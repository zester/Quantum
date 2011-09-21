#include "qwindowscreen.h"


QWindowScreen::QWindowScreen()
{
    dpy    = XOpenDisplay(NULL);
    root   = RootWindow(dpy, 0);
    xrrs   = XRRSizes(dpy, 0, &num_sizes);
    conf   = XRRGetScreenInfo(dpy, root);
    original_rate  = XRRConfigCurrentRate(conf);
    original_size_id = XRRConfigCurrentConfiguration(conf, &original_rotation);
}

short QWindowScreen::width()
{
    return xrrs[original_size_id].width;
}

short QWindowScreen::height()
{
    return xrrs[original_size_id].height;
}

short QWindowScreen::refreshRate()
{
    return original_rate;
}

short QWindowScreen::rotation()
{
    return original_rotation;
}

int QWindowScreen::screens()
{
    return XScreenCount(dpy);
}
