/*
 * $Id$
 *
 * Copyright © 2003-2004 Fredrik Höglund <fredrik@kde.org>
 *
 * The algorithm for compositing the top-level windows onto the root window
 * was borrowed from xcompmgr, copyright © 2003 Keith Packard.
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

#include <qwindowdefs.h>
#include <qrect.h>
#include <qtimer.h>
#include <qdebug.h>

#include <X11/Xlib.h>
#include <X11/extensions/Xcomposite.h>
#include <X11/Xatom.h>

//#include <X11/Xmu/WinUtil.h>

#include "workspace.h"
#include "client.h"
#include "utils.h"
#include "debug.h"
#include "extensions.h"
#include "atoms.h"

#include <iostream>

Workspace *Workspace::sInst = NULL;

extern Display *dpy;

Workspace::Workspace() : mDamage( None ), mWaitForClients( false ), mInitialRepaint( true )
{
    Extensions::initialize();

	XGrabServer( dpy );

	// Redirect all toplevel window contents to offscreen storage
	XCompositeRedirectSubwindows( dpy, rootId(), CompositeRedirectManual );

    initClientList();

	// Request notification about toplevel window state changes
	XSelectInput( dpy, rootId(),
			SubstructureNotifyMask | ExposureMask |
			StructureNotifyMask | PropertyChangeMask );

	XUngrabServer( dpy );

	// Get the picture format for the root window
	mFormat = XRenderFindVisualFormat( dpy, visual() );

	// Create an unclipped picture for drawing on the root window
	XRenderPictureAttributes pa;
	pa.subwindow_mode = IncludeInferiors;
	mFrontbuffer = XRenderCreatePicture( dpy, rootId(), format(), CPSubwindowMode, &pa );

	createBackbuffer();

	XSync( dpy, false );
}


Workspace::~Workspace()
{
	for ( ClientList::Iterator it = mList.begin(); it != mList.end(); ++it )
		delete *it;
	mList.clear();

	releasePicture( mRootTile );
	releasePicture( mBackbuffer );
	releasePicture( mFrontbuffer );

	if ( mDamage != None )
		XFixesDestroyRegion( dpy, mDamage );
}


void Workspace::createBackbuffer()
{
	Pixmap pixmap = XCreatePixmap( dpy, rootId(), width(), height(), depth() );
	mBackbuffer = XRenderCreatePicture( dpy, pixmap, format(), 0, 0 );
	XFreePixmap( dpy, pixmap ); // The picture owns the pixmap now
}


Client *Workspace::find( Window id ) const
{
	ClientList::ConstIterator end = mList.constEnd();
	for ( ClientList::ConstIterator it = mList.constBegin(); it != end; ++it )
		if ( (*it)->winId() == id )
			return *it;
	return NULL;
}


void Workspace::restack( Client *client, Window above /* the window below client */)
{
    QMutableLinkedListIterator<Client *> i(mList);
    if (i.findNext(client))
        i.remove();

	if ( above != None ) {
        i.toBack();

        while (i.hasPrevious())
        {
            if (i.previous()->winId() == above)
            {
                i.insert(client);
                break;
            }
        }

    } else {
        mList.append(client);
    }
}

void Workspace::initClientList()
{
	// Get a list of all toplevel windows from the X server, sorted bottom to top
	uint nwindows;
	Window root_return, parent_return, *windows;
	XQueryTree( dpy, rootId(), &root_return,
			&parent_return, &windows, &nwindows );

	// Create a client object for each window and insert it into the window
	// list, which is sorted top to bottom. (the opposite of the order returned
	// by XQueryTree()).
	for ( uint i = 0; i < nwindows; i++ ) {
		XWindowAttributes attr;
		if ( !XGetWindowAttributes( dpy, windows[i], &attr ) )
			continue;

		mList.prepend( new Client( windows[i], attr ) );
	}

	XFree( windows );
}

void Workspace::remove( Window id )
{
	/*
	Client *client = 0;

	ClientList::Iterator end = list.end();
	for ( ClientList::Iterator it = list.begin(); it != end; ++it ) {
		if ( (*it)->winId() == id ) {
			client = *it;
			list.remove( it );
			break;
		}
	}

	delete client;
	*/
	Client *client = find( id );
	mList.removeOne( client );
	delete client;
}


// Adds the region to the total damage for the workspace
void Workspace::addDamage( XserverRegion &region )
{
	if ( mDamage ) {
		XFixesUnionRegion( dpy, mDamage, mDamage, region );
		XFixesDestroyRegion( dpy, region );
	} else
		mDamage = region;

	region = None;
}


void Workspace::createRootTile()
{
	Pixmap pixmap = None;

	Atom actual_type;
	int actual_format;
	ulong nitems, bytes_remaining;
	uchar *data = 0L;

	// Try to find a root window property with a pixmap ID for a background pixmap.
	Atom atoms[] = { ATOM(ESETROOT_PMAP_ID), ATOM(_XROOTPMAP_ID), ATOM(_XSETROOT_ID) };
	for (int i = 0; i < 3; i++ )
	{
		int result = XGetWindowProperty( dpy, rootId(), atoms[i], 0, 4, false, XA_PIXMAP,
						&actual_type, &actual_format, &nitems, &bytes_remaining, &data );

		if ( result == Success && actual_type == XA_PIXMAP
				   && actual_format == 32 && nitems == 1 )
		{
			pixmap = *reinterpret_cast<Pixmap*>( data );
			XFree( data );
			break;
		}
	}

	XRenderPictureAttributes pa;
	pa.repeat = true;

	// Create the root tile picture for the pixmap if one was found
	if ( pixmap != None ) {
		mRootTile = XRenderCreatePicture( dpy, pixmap, format(), CPRepeat, &pa );
	} else {
		// If no background pixmap is set, create a simply 1x1 tile
		pixmap    = XCreatePixmap( dpy, rootId(), 1, 1, depth() );
		mRootTile = XRenderCreatePicture( dpy, pixmap, format(), CPRepeat, &pa );

		// Fill it with a gray color
		XRenderColor col = { 0x8080, 0x8080, 0x8080, 0xffff };
		XRenderFillRectangle( dpy, PictOpSrc, mRootTile, &col, 0, 0, 1, 1 );
	}
}


bool Workspace::allVisibleClientsPainted() const
{
	ClientList::ConstIterator end = mList.constEnd();
	for ( ClientList::ConstIterator it = mList.constBegin(); it != end; ++it ) {
		Client *client = *it;
		if ( !client->isVisible() || client->isPainted() )
			continue;

		// We don't care about windows that are positioned outside of the display
		QRect r = client->geometry( WindowAndBorder );
		if ( r.right() <= 0 || r.bottom() <= 0 || r.left() >= width() || r.top() >= height() )
			continue;

		return false;
	}

	return true;
}


// This is the function that creates the screen presentation, by compositing the
// top-level windows on the root window.
void Workspace::repaint()
{
	// If there's no damage, update the whole display
	if ( mDamage == None || mInitialRepaint ) {
		XRectangle r = { 0, 0, width(), height() };
		XserverRegion region = XFixesCreateRegion( dpy, &r, 1 );

		if ( mDamage )
			XFixesDestroyRegion( dpy, mDamage );

		mDamage = region;
		mInitialRepaint = false;
	}

	// Use the damage region as the clip region for the root window
	XFixesSetPictureClipRegion( dpy, frontBuffer(), 0, 0, mDamage );

	// Client list for clients that are either translucent, or have a shadow
	ClientList translucents;

	// Draw each opaque window top to bottom, subtracting the bounding rect of
	// each drawn window from the clip region.
	ClientList::ConstIterator end = mList.constEnd();
	for ( ClientList::ConstIterator it = mList.constBegin(); it != end; ++it )
	{
		Client *client = *it;

		if ( !client->isVisible() || !client->isPainted() )
			continue;

		// Update the region containing the area the window was last rendered at.
		client->updateOnScreenRegion();

		// Only draw the window if it's opaque
		if ( client->isOpaque() ) {
			// Set the clip region for the backbuffer to the damage region, and
			// subtract the clients shape from the damage region
			XFixesSetPictureClipRegion( dpy, backBuffer(), 0, 0, mDamage );
			XFixesSubtractRegion( dpy, mDamage, mDamage, client->shape() );

			XRenderComposite( dpy, PictOpSrc, client->picture(),
					None, backBuffer(), 0, 0, 0, 0,
					client->x(), client->y(),
					client->width() + client->borderWidth() * 2,
					client->height() + client->borderWidth() * 2 );
		}

		// Save the clip region before the next client shape is subtracted from it.
		// We need to restore it later when we're drawing the shadow.
		client->setShapeClip( mDamage );
		translucents.prepend( client );
	}

	// Draw any areas of the root window not covered by windows
	XFixesSetPictureClipRegion( dpy, backBuffer(), 0, 0, mDamage );
	XRenderComposite( dpy, PictOpSrc, rootTile(), None, backBuffer(),
					  0, 0, 0, 0, 0, 0, width(), height() );

	// Now walk the list backwards, drawing translucent windows and shadows.
	// That we draw bottom to top is important now since we're drawing translucent windows.
	end = translucents.constEnd();
	for ( ClientList::ConstIterator it = translucents.constBegin(); it != end; ++it )
	{
		Client *client = *it;

		// Restore the previously saved clip region
		XFixesSetPictureClipRegion( dpy, backBuffer(), 0, 0, client->shapeClip() );

		// Only draw the window if it's translucent
		// (we drew the opaque ones in the previous loop)
		if ( !client->isOpaque() )
			XRenderComposite( dpy, PictOpOver, client->picture(),
				    client->alphaMask(), backBuffer(), 0, 0, 0, 0,
					client->x() + client->borderWidth(),
					client->y() + client->borderWidth(),
					client->width(), client->height() );

		// We don't need the clip region anymore
		client->destroyShapeClip();
	}

	translucents.clear();

	// Destroy the damage region
	XFixesDestroyRegion( dpy, mDamage );
	mDamage = None;

	// Copy the back buffer contents to the root window
	XFixesSetPictureClipRegion( dpy, backBuffer(), 0, 0, None );
	XRenderComposite( dpy, PictOpSrc, backBuffer(), None, frontBuffer(),
					  0, 0, 0, 0, 0, 0, width(), height() );
}


void Workspace::createNotifyEvent( const XCreateWindowEvent *event )
{
	XWindowAttributes attr;
	if ( !XGetWindowAttributes( dpy, event->window, &attr ) )
		return;

	Client *client = new Client( event->window, attr );
	mList.prepend( client ); // Insert it at the top of the list
}


// Move, resize, or stacking order change
void Workspace::configureNotifyEvent( const XConfigureEvent *event )
{
	Client *client = find( event->window );

	if ( client ) {
		QRect geometry = QRect( event->x, event->y, event->width, event->height );
		int borderWidth = event->border_width;
		Window above = event->above;

		// Compress configure events. There's no need to union each of these rects with
		// the damage region, since there are only two visibly affected rects; the rect
		// where the window is currently drawn, and the rect in the last configure event,
		// which is where we'll draw the window in the next paint cycle.
		XConfigureEvent e;
		while ( XCheckTypedWindowEvent( dpy, client->winId(), ConfigureNotify, (XEvent*)&e ) )
		{
			geometry = QRect( e.x, e.y, e.width, e.height );
			borderWidth = e.border_width;
			above = e.above;
		}

		client->geometryChanged( geometry, borderWidth );
		restack( client, above );
	} else if ( event->window == rootId() ) {
		// Recreate the back buffer
		releasePicture( mBackbuffer );
		createBackbuffer();
	}
}


void Workspace::shapeNotifyEvent( const XShapeEvent *event )
{
	// Notify the client that its shape has changed
	Client *client = find( event->window );
	if ( client )
		client->shapeChanged();
}


void Workspace::reparentNotifyEvent( const XReparentEvent *event )
{
	//std::cout << "got reparent event for window "
	//	<< std::hex << event->window << std::endl;

	if ( event->parent == rootId() ) {
		XWindowAttributes attr;
		if ( !XGetWindowAttributes( dpy, event->window, &attr ) )
			return;

		//std::cout << "window " << std::hex << event->window << " reparented to root\n";
		Client *client = new Client( event->window, attr );
		mList.prepend( client );
	} else {
		//std::cout << "window " << std::hex << event->window << " reparented to "
		//		<< event->parent << std::endl;
		remove( event->window );
	}
}


void Workspace::circulateNotifyEvent( const XCirculateEvent *event )
{
	Client *client = find( event->window );
	if ( client ) {
		Window above = ( event->place == PlaceOnTop ) ? mList.first()->winId() : None;
		restack( client, above );
	}
}


// Handles expose events for the root window
void Workspace::exposeEvent( const XExposeEvent *event )
{
	if ( event->window != rootId() )
		return;

	int more = event->count + 1;
	if ( mExposeRects.count() + more > mExposeRects.capacity() )
		mExposeRects.reserve( mExposeRects.count() + more );

	XRectangle r = { event->x, event->y, event->width, event->height };
	mExposeRects.append( r );

	if ( event->count == 0 ) {
		XserverRegion damage = XFixesCreateRegion( dpy,
					&mExposeRects.first(), mExposeRects.count() );
		addDamage( damage );
		mExposeRects.clear();
	}
}


void Workspace::damageNotifyEvent( const XDamageNotifyEvent *event )
{
	Client *client = find( event->drawable );

	// ### should never happen
	if ( !client )
		return;

	XserverRegion parts;

	if ( !client->isPainted() ) {
		// If the window has been painted for the first time, mark the whole
		// window as damaged.
		parts = client->createRegion( WindowAndBorder );
		XDamageSubtract( dpy, client->damageHandle(), None, None );
		client->setPainted( true );
	} else {
		// Create a new empty region
		parts = XFixesCreateRegion( dpy, 0, 0 );

		// Copy the damage region to parts, subtracting it from the widgets damage
		XDamageSubtract( dpy, client->damageHandle(), None, parts );

		// Offset parts with the widgets position
		XFixesTranslateRegion( dpy, parts, client->x(), client->y() );
	}

	// Add the damaged region to the total damage for the workspace
	// (destroys parts)
	addDamage( parts );
}


static Bool windowOpacityPredicate( Display *, XEvent *event, XPointer arg )
{
	if ( event->type == PropertyNotify
         && event->xproperty.atom == ATOM(_NET_WM_WINDOW_OPACITY)
			&& event->xproperty.window == Window( arg ) )
		return True;

	return False;
}

static Bool rootPixmapPredicate( Display *, XEvent *event, XPointer arg )
{
	if ( event->type == PropertyNotify && event->xproperty.window == Window( arg ) &&
         ( event->xproperty.atom == ATOM(_XROOTPMAP_ID) ||
           event->xproperty.atom == ATOM(_XSETROOT_ID)  ||
           event->xproperty.atom == ATOM(ESETROOT_PMAP_ID) ) )
		return True;

	return False;
}

void Workspace::propertyNotifyEvent( const XPropertyEvent *event )
{
	//char *name = XGetAtomName( dpy, event->atom );
	//std::cout << "property \"" << name << "\" changed.\n";
	//XFree( name );


	// Handle property events for the root window
	if ( event->window == rootId() ) {
		// Major optimization when switching desktops; we'll block updates and just
		// let damage accumulate until all newly mapped windows have been painted.
		if ( event->atom == ATOM(_NET_CURRENT_DESKTOP) )
		{
			mWaitForClients = true;
			XSync( dpy, false ); // Helps to accumulate more events
		}

		// If the root window pixmap was changed
		else if ( event->atom == ATOM(_XROOTPMAP_ID) ||
		          event->atom == ATOM(_XSETROOT_ID)  ||
		          event->atom == ATOM(ESETROOT_PMAP_ID) )
		{
			// Compress these events
			XEvent dummy;
			while ( XCheckIfEvent( dpy, &dummy, rootPixmapPredicate, XPointer( rootId() ) ) );

			// Destroy the root tile picture
			releasePicture( mRootTile );

			// Damage the whole display
			XserverRegion r = createRegionFromQRect( QRect( 0, 0, width(), height() ) );
			addDamage( r );
		}
	}

	// Handle notifications of changes to window opacity hints
	else if ( event->atom == ATOM(_NET_WM_WINDOW_OPACITY))
	{
		// Compress opacity change events for the window
		XEvent dummy;
		while ( XCheckIfEvent( dpy, &dummy, windowOpacityPredicate, XPointer(event->window) ) );

		Client *client = find( event->window );
		if ( client )
			client->opacityChanged();
	}
}


bool Workspace::x11Event( XEvent *event )
{
	//bool dumpWindows = false;
	//bool reportNextUpdate = false;

    static int debugs = 0;
    qDebug() << ++debugs << __PRETTY_FUNCTION__ << "got event" << eventName(event->type);

	switch ( event->type ) {
		case CreateNotify:
			createNotifyEvent( &event->xcreatewindow );
			//std::cout << "window " << std::hex << event->xcreatewindow.window << " created\n";
			//dumpWindows = true;
			break;

		case DestroyNotify:
			remove( event->xdestroywindow.window );
			//std::cout << "window " << std::hex << event->xdestroywindow.window << " destroyed\n";
			//dumpWindows = true;
			break;

		case ConfigureNotify:
			configureNotifyEvent( &event->xconfigure );
			//std::cout << "window " << std::hex << event->xconfigure.window << " configured\n";
			break;

		case MapNotify:
			if ( Client *client = find( event->xmap.window ) )
				client->show();
			//dumpWindows = true;
			//std::cout << "window " << std::hex << event->xmap.window << " mapped\n";
			break;

		case UnmapNotify:
			if ( Client *client = find( event->xunmap.window ) )
				client->hide();
			//dumpWindows = true;
			//std::cout << "window " << std::hex << event->xunmap.window << " unmapped\n";
			break;

		case ReparentNotify:
			reparentNotifyEvent( &event->xreparent );
			//dumpWindows = true;
			break;

		case CirculateNotify:
			circulateNotifyEvent( &event->xcirculate );
			//std::cout << "circulate event\n";
			break;

		case Expose:
			exposeEvent( &event->xexpose );
			break;

		case PropertyNotify:
			propertyNotifyEvent( &event->xproperty );
			break;

		default:
			if ( event->type == Extensions::damageEvent(XDamageNotify) )
				damageNotifyEvent( reinterpret_cast< XDamageNotifyEvent * >( event ) );
			
			else if ( event->type == Extensions::shapeEvent(ShapeNotify ))
				shapeNotifyEvent( reinterpret_cast< XShapeEvent * >( event ) );
	}

	/*
	if ( dumpWindows ) {
		std::cout << "===Clients===\n";
		ClientList::ConstIterator end = mList.constEnd();
		for (ClientList::ConstIterator it = mList.constBegin(); it != end; ++it) {
			Client *client = *it;

			//if (!client->isVisible() || client->width() <= 10 || client->height() <= 10)
			//	continue;

			Window target = XmuClientWindow( dpy, client->winId() );

			XTextProperty tp;
			XGetWMName( dpy, target, &tp );
			std::cout << std::hex << client->winId() << " "
					<< (client->isVisible() ? "(mapped)" : "(not mapped)")
					<< " " << std::dec << client->width() << "x" << client->height() << ": ";

			for (uint i = 0; i < tp.nitems; i++)
				std::cout << (char)tp.value[i];
			std::cout << std::endl;
		}
		//std::cout << "=============\n";
		std::cout << std::endl;
	}
	*/

	// Update the root window if there's damage and there are no more events pending
	if ( mDamage && QLength( dpy ) == 0 ) {
		if ( mWaitForClients && !allVisibleClientsPainted() )
		{
			//std::cout << "delaying update.\n.";
		} else {
			mWaitForClients = false;
			repaint();
		}

		// Helps to accumulate more events
		XSync( dpy, false );
	}

	return false;
}


