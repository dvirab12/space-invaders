#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <SDL2/SDL.h>

#define SCREEN_HEIGHT 1280
#define SCREEN_WIDTH 720

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;

bool init();

int main(int argc, char* args[]) {
    init();
    if(!init()) {
        printf("Failed to init! SDL_Error: %s\n", SDL_GetError());
        return -1;
    } 

    SDL_Event event;
    bool quit = false;
    while (!quit) {

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        //TODO Input!
    }
    close();
    return 0;
}

int init() {
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Failed to init SDL, SDL_Error: %s\n", SDL_GetError());
        success = false;
    }

    gWindow = SDL_CreateWindow("Dvir's Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (gWindow == NULL) {
        printf("Failed to init Window, SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    gScreenSurface = SDL_GetWindowSurface(gWindow); 

    return success;
}

bool close() {
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    SDL_Quit();
}

