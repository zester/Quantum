/*
 * $Id$
 *
 * Copyright © 2003-2004 Fredrik Höglund <fredrik@kde.org>
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of Fredrik Höglund not be used in
 * advertising or publicity pertaining to distribution of the software without
 * specific, written prior permission.  Fredrik Höglund makes no
 * representations about the suitability of this software for any purpose.  It
 * is provided "as is" without express or implied warranty.
 *
 * FREDRIK HÖGLUND DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL FREDRIK HÖGLUND BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

#include "client.h"

#include <X11/Xatom.h>
#include <X11/extensions/Xcomposite.h>

#include "utils.h"
#include "atoms.h"

#include <iostream>

// Declared and interned in main.cpp
extern Display *dpy;


Client::Client( Window win, const XWindowAttributes &attr )
	: mId( win ),
	  mPixmap( None ),
	  mPicture( None ),
	  mAlphaPict( None ),
	  mOpacity( 0xffffffff ),
	  mDamage( None ),
	  mGeometry( 0, 0, 0, 0 ),
	  mBorderWidth( 0 ),
	  mVisibleRegion( None ),
	  mShapeRegion( None ),
	  mShapeClipRegion( None ),
	  mVisible( attr.map_state == IsViewable ),
	  mPainted( false ),
	  mSourceClipValid( false ),
	  mAlphaChannel( false ),
	  mOverrideRedirect( attr.override_redirect )
{
	if ( attr.c_class != InputOnly )
	{
		// Find the window pixel format
		mFormat = XRenderFindVisualFormat( dpy, attr.visual );

		// Check if the window has an alpha channel
		if ( mFormat && mFormat->type == PictTypeDirect && mFormat->direct.alphaMask )
			setHasAlphaChannel( true );

		// Create the damage object
		mDamage = XDamageCreate( dpy, winId(), XDamageReportNonEmpty );

		// Make sure we get notified when the window shape is changed
		XShapeSelectInput( dpy, winId(), ShapeNotifyMask );
	}

	// Initialize the geometry
	mGeometry = QRect( attr.x, attr.y, attr.width, attr.height );
	mBorderWidth = attr.border_width;

	// Make the window visible if it's mapped
	if ( isVisible() )
		show();
}


Client::~Client()
{
	releaseRegion( mVisibleRegion );
	releaseRegion( mShapeRegion );
	releaseRegion( mShapeClipRegion );

	releasePixmap( mPixmap );
	releasePicture( mPicture );
	releasePicture( mAlphaPict );

	if ( mDamage )
		XDamageDestroy( dpy, mDamage );
}


// Creates the window picture
void Client::createWindowPicture()
{
	// Increase the ref count for the backing pixmap
	if ( !mPixmap )
		mPixmap = XCompositeNameWindowPixmap( dpy, winId() );

	// Create the window picture
	mPicture = XRenderCreatePicture( dpy, mPixmap, mFormat, 0, 0 );
}

// This function gets called when the window geometry is changed.
void Client::geometryChanged( const QRect &newGeometry, int newBorderWidth )
{
	// Destroy the cached shape region since it's no longer valid
	releaseRegion( mShapeRegion );

	// If the window has been resized
	if ( width() != newGeometry.width() || height() != newGeometry.height()
			|| borderWidth() != newBorderWidth )
	{
		// Deref the now stale backing pixmap, and free the picture
		releasePixmap( mPixmap );
		releasePicture( mPicture );

		mSourceClipValid = false;
	}

	mGeometry    = newGeometry;
	mBorderWidth = newBorderWidth;

	if ( !isVisible() )
		return;

	// Create an empty region and initialize it with the current visible region
	XserverRegion damage = XFixesCreateRegion( dpy, 0, 0  );
	if ( mVisibleRegion != None )
		XFixesCopyRegion( dpy, damage, mVisibleRegion );

	// Create a region with the new geometry, and union it with the old
	XserverRegion region = createRegion( WindowAndBorder );
	XFixesUnionRegion( dpy, damage, damage, region );
	XFixesDestroyRegion( dpy, region );

	// Add the region to the workspace's damage
	Workspace::instance()->addDamage( damage );
}


// This function gets called when the windows shape is changed.
// (using the XShape extension)
void Client::shapeChanged()
{
	// Destroy the cached shape region since it's no longer valid
	releaseRegion( mShapeRegion );

	mSourceClipValid = false;

	// Damage the whole window (destroys mVisibleRegion)
	Workspace::instance()->addDamage( mVisibleRegion );
}


// Called when the opacity property has been changed
void Client::opacityChanged()
{
	ulong opacity = getWindowOpacity();
	if ( opacity == mOpacity )
		return;

	mOpacity = opacity;

	if ( mAlphaPict && mOpacity == 0xffffffff )
		releasePicture( mAlphaPict );

	else if ( mOpacity < 0xffffffff ) {
		if ( mAlphaPict ) {
			XRenderColor col = { 0, 0, 0, mOpacity >> 16 };
			XRenderFillRectangle( dpy, PictOpSrc, mAlphaPict, &col, 0, 0, 1, 1 );
		} else
			createOpacityMask();
	}

	// When the opacity is changed the whole window needs to be redrawn
	XserverRegion extents = createRegion( WindowAndBorder );
	Workspace::instance()->addDamage( extents );
}


// Returns the window geometry of the specified extents
QRect Client::geometry( ShapeType type ) const
{
	QRect r;

	switch ( type )
	{
		case WindowAndBorder:
			r = QRect( x(), y(), width() + borderWidth() * 2, height() + borderWidth() * 2 );
			break;

		case WindowOnly:
			r = QRect( x() + borderWidth(), y() + borderWidth(), width(), height() );
			break;

		default:
			r = QRect();
	}

	return r;
}


// Creates and returns a region object of the specified type.
// WindowOnly is a region that matches the window shape precisely.
// WindowAndBorder is a region that matches the window shape + X border
// WindowAndShadow is a region that matches the window shape + X border and shadow.
// Shadow is a region that only contains the shadow
XserverRegion Client::createRegion( ShapeType type ) const
{
	XserverRegion region;

	switch ( type )
	{
		// Region matching the window shape, minus the X border
		case WindowOnly:
			region = XFixesCreateRegionFromWindow( dpy, winId(), WindowRegionBounding );
			XFixesTranslateRegion( dpy, region, x() + borderWidth(), y() + borderWidth() );
			break;

		// All other region types
		default:
			region = createRegionFromQRect( geometry( type ) );
	}

	return region;
}


// Returns a cached copy of the windows' shape region, creating it if necessary.
XserverRegion Client::shape()
{
	if ( mShapeRegion == None )
		mShapeRegion = createRegion( WindowOnly );

	return mShapeRegion;
}


// Updates or initializes the region with the bounding rectangle for the window and its shadow,
// as they appear on the screen. This function is only called when updating the root window.
void Client::updateOnScreenRegion()
{
	if ( mVisibleRegion != None )
		XFixesDestroyRegion( dpy, mVisibleRegion );

	mVisibleRegion = createRegion( WindowAndBorder );
}


// Marks the window as visible so it will be drawn the next time the root window is updated.
// This function doesn't add the window extents rect to the workspace damage since we'll
// receive damage notify events as soon as the window is drawn by the client.
void Client::show()
{
	// Listen for EWMH changes
	XSelectInput( dpy, winId(), PropertyChangeMask );
	mOpacity = getWindowOpacity();

	mVisible = true;
	mPainted = false;
}


// Marks the window as hidden so it won't be drawn when the root window is updated
void Client::hide()
{
	if ( !isVisible() )
		return;

	mVisible         = false;
	mPainted         = false;
	mSourceClipValid = false;

	releasePixmap( mPixmap );      // Deref the backing pixmap
	releasePicture( mPicture );    // Free the window picture
	releasePicture( mAlphaPict );  // Free the opacity mask
	
	// Stop listening for EWMH changes
	XSelectInput( dpy, winId(), NoEventMask );

	// When a window is hidden, add the windows' visible region to the workspace's
	// damage so the underlying windows are redrawn. This is necessary since they
	// won't receive expose events when this happens.
	// (The composite extension provides backing-store.)
	if ( mVisibleRegion != None )
		Workspace::instance()->addDamage( mVisibleRegion ); // Destroys mVisibleRegion
}


// Reads the _NET_WM_WINDOW_OPACITY hint from the window, and returns the value.
// Returns 0xffffffff (opaque) if unsuccessful, or the value isn't set.
ulong Client::getWindowOpacity() const
{
	Atom actual;
	int format;
	ulong nitems, left;
	ulong opacity = 0xffffffff;
	uchar *data = 0L;
	int result;

	result = XGetWindowProperty( dpy, winId(), ATOM(_NET_WM_WINDOW_OPACITY), 0, 1,
				false, XA_CARDINAL, &actual, &format, &nitems, &left, &data );

	if ( result == Success && actual == XA_CARDINAL && format == 32
			&& nitems == 1 && left == 0 && data )
		opacity = *reinterpret_cast< ulong* >( data );

	if ( data )
		XFree( data );

	return opacity;
}


// Creates the 1x1 8 bit alpha mask used for drawing non-opaque windows
void Client::createOpacityMask()
{
    XRenderPictFormat *format = XRenderFindStandardFormat( dpy,
							   !isOpaque() ? PictStandardARGB32 : PictStandardA8 );
	XRenderPictureAttributes pa;
	pa.repeat = true;

	Pixmap pixmap = XCreatePixmap( dpy, DefaultRootWindow( dpy ), 1, 1, !isOpaque() ? 32 : 8 );
	mAlphaPict = XRenderCreatePicture( dpy, pixmap, format, CPRepeat, &pa );
	XFreePixmap( dpy, pixmap );

	XRenderColor col;
	col.alpha = mOpacity >> 16;
	XRenderFillRectangle( dpy, PictOpSrc, mAlphaPict, &col, 0, 0, 1, 1 );
}

