#include <X11/Xlib.h>
#include <stdio.h>

using namespace std;

int main()
{
    Display *display = XOpenDisplay(NULL);
    int screen = DefaultScreen(display);

    Window root = XDefaultRootWindow(display);
    int win_width = DisplayWidth(display, screen);
    int win_height = DisplayHeight(display, screen);

    XSetWindowAttributes attrs;
    attrs.override_redirect = true;
    attrs.background_pixel = XBlackPixel(display, screen);

    Window win = XCreateWindow(
        display, root,
        0, 0,
        win_width, win_height,
        0,
        DefaultDepth(display, screen),
        InputOutput,
        DefaultVisual(display, screen),
        CWOverrideRedirect,
        &attrs
    );

    XMapWindow(display, win);
    XLowerWindow(display, win);
    XFlush(display);

    while(1){};


    XCloseDisplay(display);
    return 0;
}
