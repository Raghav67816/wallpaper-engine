#include <X11/Xlib.h>
#include <iostream>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <vector>
#include <X11/extensions/XShm.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;

int c_frame = 0;
int frames = 30;


vector<unsigned char*> load_frames(){
    vector<unsigned char*> frames;
    int w, h, channels;
    for (int i=0; i<150; i++){
        frames.assign(
            i, stbi_load(to_string(i).c_str() + '.jpg', &w, &h, &channels, 3)
        );
    }
    return frames;
}

int main()
{
    int w, h;
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
        InputOnly,
        DefaultVisual(display, screen),
        CWOverrideRedirect,
        &attrs
    );

    XShmSegmentInfo *shm_info;
    XImage* img = XShmCreateImage(
        display, 
        DefaultVisual(display, screen),
        24,
        ZPixmap,
        NULL,
        shm_info,
        w, h
    );

    vector<unsigned char*> frames = load_frames();
    cout << "done loading" << endl;

    while(1){

    };

    XMapWindow(display, win);
    XLowerWindow(display, win);
    XFlush(display);

    XCloseDisplay(display);
    return 0;
}
