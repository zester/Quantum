extern Display *dpy;

inline void releasePicture( Picture &picture )
{
	if ( picture ) {
		XRenderFreePicture( dpy, picture );
		picture = None;
	}
}

inline void releasePixmap( Pixmap &pixmap )
{
	if ( pixmap ) {
		XFreePixmap( dpy, pixmap );
		pixmap = None;
	}
}

inline void releaseRegion( XserverRegion &region )
{
	if ( region ) {
		XFixesDestroyRegion( dpy, region );
		region = None;
	}
}

inline XserverRegion createRegionFromQRect( const QRect &r )
{
	XRectangle rect = { r.x(), r.y(), r.width(), r.height() };
	return XFixesCreateRegion( dpy, &rect, 1 );
}


