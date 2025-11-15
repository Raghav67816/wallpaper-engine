#include <SDL2/SDL.h>
#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_syswm.h>
#include <vector>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>

using namespace std;

struct WinDim{
    int width;
    int height;
};

WinDim get_window_dim(){
    Display *display = XOpenDisplay(NULL);
    if(!display){
        cout << "failed to open display" << endl;
    }
    int screen = XDefaultScreen(display);
    Window root = XRootWindow(display, screen);

    XWindowAttributes root_attrs;
    XGetWindowAttributes(display, root, &root_attrs);
    XCloseDisplay(display);

    WinDim dim = {root_attrs.width, root_attrs.height};
    return dim;
}

vector<SDL_Texture*> load_textures(SDL_Renderer* renderer){
    vector<SDL_Texture*> textures;
    for (int i=0; i<150; i++){
        string fname = "snowfall/" + to_string(i) + ".jpg";
        cout << fname << endl;
        SDL_Texture *texture = IMG_LoadTexture(
            renderer, fname.c_str()
        );
        if(!texture){
            cout << i << " not loaded" << endl;
        }
        textures.push_back(texture);
    }
    cout << "Done loading textures" << endl;
    return textures;
}

void lower_window(SDL_Window *window){
    SDL_SysWMinfo win_info;
    if(SDL_GetWindowWMInfo(window, &win_info)){
        Display *display = win_info.info.x11.display;
        Window x_win = win_info.info.x11.window;

        XLowerWindow(display, x_win);

        Atom wm_type = XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        Atom wm_type_desktop = XInternAtom(display, "_NET_WM_WINDOW_TYPE_DESKTOP", False);

        XFlush(display);
    }
}

int main(int argc, char** args){
    int c_frame = 0;
    const int frameDelay = 1000/30;
    Uint32 frameStart;
    int frameTime;
    WinDim dim = get_window_dim();

    if(SDL_Init(SDL_INIT_EVERYTHING | IMG_Init(IMG_INIT_JPG)) != 0){
        cout << "failed to init SDL" << endl;
    }


    SDL_Window *window = SDL_CreateWindow(
        "Wallpaper Engine", 0, 0, dim.width, dim.height, 
        SDL_WINDOW_FULLSCREEN | SDL_WINDOW_BORDERLESS
    );

    lower_window(window);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if(!renderer){
        cout << "failed to create renderer" << endl;
        cout << SDL_GetError() << endl;
    }
    SDL_Surface *surface = SDL_GetWindowSurface(window);

    vector<SDL_Texture*> frames = load_textures(renderer);

    SDL_UpdateWindowSurface(window);

    if (!window){
        cout << "failed to create a window." << endl;
    }

    SDL_Event event;
    bool running = true;

    while(running){
        frameStart = SDL_GetTicks();

        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                running = false;
            }
        }

        
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, frames[c_frame], NULL, NULL);
        SDL_RenderPresent(renderer);
        
        c_frame = (c_frame + 1) % frames.size();


        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime){
            SDL_Delay(frameDelay - frameTime);
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
