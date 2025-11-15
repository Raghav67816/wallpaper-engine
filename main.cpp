#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

int main(int argc, char** args){
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        cout << "failed to init SDL" << endl;
    }

    SDL_Window *window = SDL_CreateWindow(
        "Wallpaper Engine", 0, 0, 800, 600, SDL_WINDOW_SHOWN
    );
    SDL_Surface *surface = SDL_GetWindowSurface(window);

    SDL_UpdateWindowSurface(window);

    if (!window){
        cout << "failed to create a window." << endl;
    }

    SDL_Event event;
    bool running = true;

    while(running){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                running = false;
            }
        }

        SDL_Delay(16);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
