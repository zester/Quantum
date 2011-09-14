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

#ifndef __CLIENT_H
#define __CLIENT_H

#include <QRect>

#include "workspace.h"

enum ShapeType { WindowOnly, WindowAndBorder };

class Client
{
	public:
		Client( Window id, const XWindowAttributes & );
		~Client();

		bool hasAlphaChannel() const { return mAlphaChannel; }
		bool isOpaque() const;
		bool isOverrideRedirect() const { return mOverrideRedirect; }
		void setHasAlphaChannel( bool value ) { mAlphaChannel = value; }

		Window winId() const { return mId; }
		Damage damageHandle() const { return mDamage; }
		Picture picture();

		XserverRegion createRegion( ShapeType type ) const;

		XserverRegion shape(); // Region covering only the window
		void updateOnScreenRegion();

		inline void setShapeClip( const XserverRegion );
		XserverRegion shapeClip() { return mShapeClipRegion; }
		inline void destroyShapeClip();

		int x() const { return mGeometry.x(); }
		int y() const { return mGeometry.y(); }
		int width() const { return mGeometry.width(); }
		int height() const { return mGeometry.height(); }
		int borderWidth() const { return mBorderWidth; }
		QRect geometry( ShapeType ) const;
		Picture alphaMask();
		double opacity() const { return double( mOpacity ) / 0xffffffff; }

		void setPainted( bool painted ) { mPainted = painted; }

		void geometryChanged( const QRect &newGeometry, int newBorderWidth );
		void shapeChanged();
		void opacityChanged();

		void show();
		void hide();

		bool isVisible() const { return mVisible; }

		// Returns true if the window has been painted since it was last shown (mapped).
		bool isPainted() const { return mPainted; }


	private:
		void createWindowPicture();
		void createOpacityMask();
		ulong getWindowOpacity() const;

		Window              mId;
		XRenderPictFormat  *mFormat;
		Pixmap              mPixmap;
        Picture             mPicture, mAlphaPict;
		quint32            mOpacity;
		Damage              mDamage;
		QRect               mGeometry;
		int                 mBorderWidth;
		XserverRegion       mVisibleRegion;
		XserverRegion       mShapeRegion;
		XserverRegion       mShapeClipRegion;
		bool                mVisible:1;
		bool                mPainted:1;
		bool                mSourceClipValid:1;
		bool                mAlphaChannel:1;
		bool                mOverrideRedirect:1;
};


inline bool Client::isOpaque() const
{
	if ( hasAlphaChannel() || mOpacity < 0xffffffff )
		return false;

	return true;
}


inline Picture Client::picture()
{
	if ( !mPicture )
		createWindowPicture();

	// ### There's room for optimization here. The window picture only needs a clip region when it's
	// translucent. For opaque windows it doesn't matter since we're drawing them top -> bottom.
	if ( !mSourceClipValid ) {
		XserverRegion clip = XFixesCreateRegionFromWindow( dpy, winId(), WindowRegionBounding );
		XFixesSetPictureClipRegion( dpy, mPicture, 0, 0, clip );
		XFixesDestroyRegion( dpy, clip );
		mSourceClipValid = true;
	}

	return mPicture;
}

inline Picture Client::alphaMask()
{
	if ( mOpacity == 0xffffffff )
		return None;

	if ( !mAlphaPict )
		createOpacityMask();

	return mAlphaPict;
}


inline void Client::destroyShapeClip()
{
	if ( mShapeClipRegion ) {
		XFixesDestroyRegion( dpy, mShapeClipRegion );
		mShapeClipRegion = None;
	}
}


inline void Client::setShapeClip( const XserverRegion r )
{
	if ( !mShapeClipRegion )
		mShapeClipRegion = XFixesCreateRegion( dpy, 0, 0 );
	XFixesCopyRegion( dpy, mShapeClipRegion, r );
}

#endif

