#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

int main()
{
    Display *dpy;
    Window w;
    XEvent event;
    XSizeHints sizehints;

    dpy = XOpenDisplay(NULL);
    if (dpy == NULL) {
        fprintf(stderr, "Error: could not open display\n");
        exit(1);
    }

    w = XCreateSimpleWindow(dpy, DefaultRootWindow(dpy), 0, 0, 640, 480, 0, 0, WhitePixel(dpy, DefaultScreen(dpy)));
    XMapWindow(dpy, w);

    // Set size hints to make the window unresizable
    sizehints.flags = PMinSize | PMaxSize;
    sizehints.min_width = sizehints.max_width = 640;
    sizehints.min_height = sizehints.max_height = 480;
    XSetWMNormalHints(dpy, w, &sizehints);

    while (1) {
        XNextEvent(dpy, &event);
    }

    XCloseDisplay(dpy);
    return 0;
}

