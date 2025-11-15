#include <SDL2/SDL.h>
#include <iostream>
#include <SDL2/SDL_image.h>
#include <vector>
#include <string.h>

using namespace std;

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

int main(int argc, char** args){
    int c_frame = 0;

    if(SDL_Init(SDL_INIT_EVERYTHING | IMG_Init(IMG_INIT_JPG)) != 0){
        cout << "failed to init SDL" << endl;
    }

    SDL_Window *window = SDL_CreateWindow(
        "Wallpaper Engine", 0, 0, 800, 600, SDL_WINDOW_SHOWN
    );
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
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                running = false;
            }
        }

        c_frame += 1;
        if (c_frame >= 149){
            c_frame = 0;
        }
        cout << c_frame << endl;
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, frames[c_frame], NULL, NULL);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
