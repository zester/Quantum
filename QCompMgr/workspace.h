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

#ifndef __WORKSPACE_H
#define __WORKSPACE_H

#include <QVector>
#include <QObject>
#include <QLinkedList>

#include <X11/Xlib.h>
#include <X11/extensions/Xdamage.h>
#include <X11/extensions/Xfixes.h>
#include <X11/extensions/Xrender.h>
#include <X11/extensions/shape.h>

class Client;

extern Display *dpy;

class Workspace
{
	public:
		typedef QLinkedList< Client * > ClientList;

		static inline Workspace *instance();
		~Workspace();

		int width() const { return DisplayWidth( dpy, DefaultScreen(dpy) ); }
		int height() const { return DisplayHeight( dpy, DefaultScreen(dpy) ); }
		Picture frontBuffer() const { return mFrontbuffer; }
		Picture backBuffer() const { return mBackbuffer; }
		Visual *visual() const { return DefaultVisual( dpy, DefaultScreen(dpy) ); }
		XRenderPictFormat *format() const { return mFormat; }
		int depth() const { return DefaultDepth( dpy, DefaultScreen(dpy) ); }
		Window rootId() const { return RootWindow( dpy, DefaultScreen(dpy) ); }
		Picture rootTile();
		void createRootTile();

		void createBackbuffer();

		Client *find( Window ) const;
		void remove( Window );
		bool damaged() const { return mDamage != None; }
		void addDamage( XserverRegion & );
		bool allVisibleClientsPainted() const;
		void repaint();

		void createNotifyEvent( const XCreateWindowEvent * );
		void destroyNotifyEvent( const XDestroyWindowEvent * );
		void configureNotifyEvent( const XConfigureEvent * );
		void shapeNotifyEvent( const XShapeEvent * );
		void reparentNotifyEvent( const XReparentEvent * );
		void circulateNotifyEvent( const XCirculateEvent * );
		void exposeEvent( const XExposeEvent * );
		void damageNotifyEvent( const XDamageNotifyEvent * );
		void propertyNotifyEvent( const XPropertyEvent * );

		bool x11Event( XEvent * );

	private:
		Workspace();
		void restack( Client *, Window );
    void initClientList();

	private:
		static Workspace *sInst;
		int mDamageBase;
		int mShapeBase;

		XRenderPictFormat *mFormat;
		ClientList mList;
		Damage mDamage;
		Picture mBackbuffer, mFrontbuffer;
		Picture mRootTile;
		QVector< XRectangle > mExposeRects;
		bool mUpdatePending:1;
		bool mWaitForClients:1;
		bool mInitialRepaint:1;
};

Workspace *Workspace::instance()
{
	if ( !sInst )
		sInst = new Workspace;
	return sInst;
}

inline Picture Workspace::rootTile()
{
	if ( !mRootTile )
		createRootTile();

	return mRootTile;
}

#endif

