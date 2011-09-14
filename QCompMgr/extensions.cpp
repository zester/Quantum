/*
 * KDE Composite Manager, 
 * Copyright (C) 2003-2005 Fredrik HÃ¶glund <fredrik@kde.org>
 *
 * Based on xcompmgr,
 * Copyright (C) 2003 Keith Packard <keithp@keithp.com>
 *
 * Internal structure and naming style inspired by KWin,
 * Copyright (C) 1999, 2000 Matthias Ettrich <ettrich@kde.org>
 * Copyright (C) 2003 Lubos Lunak <l.lunak@kde.org>
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of Fredrik HÃ¶glund not be used in
 * advertising or publicity pertaining to distribution of the software without
 * specific, written prior permission.  Fredrik HÃ¶glund makes no
 * representations about the suitability of this software for any purpose.  It
 * is provided "as is" without express or implied warranty.
 *
 * FREDRIK HÃGLUND DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL FREDRIK HÃGLUND BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

#include "extensions.h"

#include <QDebug>

#include <X11/Xlib.h>
#include <X11/extensions/Xrender.h>
#include <X11/extensions/shape.h>
#include <X11/extensions/Xfixes.h>
#include <X11/extensions/Xdamage.h>
#include <X11/extensions/Xcomposite.h>

extern Display *dpy;

int Extensions::sShapeEventBase  = 0;
int Extensions::sDamageEventBase = 0;

bool Extensions::initialize()
{
	int eventBase, errorBase;

	qDebug() << dpy;
	
	if ( !XShapeQueryExtension( dpy, &sShapeEventBase, &errorBase ) ) {
	    qFatal("Missing the XShape extension.");
	    
	}

	if ( !XRenderQueryExtension( dpy, &eventBase, &errorBase ) ) {
	    qFatal("Missing the XRender extension.");
	    
	}

	if ( !XCompositeQueryExtension( dpy, &eventBase, &errorBase ) ) {
	    qFatal("Missing the XComposite extension.");
	    
	}

	if ( !XDamageQueryExtension( dpy, &sDamageEventBase, &errorBase ) ) {
	    qFatal("Missing the XDamage extension.");
	    
	}

	if ( !XFixesQueryExtension( dpy, &eventBase, &errorBase ) ) {
	    qFatal("Missing the XFixes extension.");
	}

	return true;
}
