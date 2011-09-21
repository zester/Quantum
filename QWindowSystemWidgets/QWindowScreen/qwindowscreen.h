#ifndef QWINDOWSCREEN_H
#define QWINDOWSCREEN_H

#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>

#include "QWindowScreen_global.h"


class QWINDOWSCREENSHARED_EXPORT QWindowScreen {
public:
    QWindowScreen();
    short width();
    short height();
    short refreshRate();
    short rotation();
    int screens();

private:
    Display                 *dpy;
    Window                  root;
    XRRScreenSize           *xrrs;
    XRRScreenConfiguration  *conf;
    Rotation original_rotation;
    int num_sizes;
    SizeID original_size_id;
    short original_rate;
};

#endif // QWINDOWSCREEN_H
