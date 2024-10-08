#include "sprites.cpp"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <string>

#define SCREEN_HEIGHT 720
#define SCREEN_WIDTH 1280

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Renderer* gRenderer = NULL;
int playerSpeed = 5;

LTexture enemysSheet;

SDL_Rect rect = {SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100, 50, 50};

void close();
bool init();

int main(int argc, char* args[]) {
    if(!init()) {
        printf("Failed to init! SDL_Error: %s\n", SDL_GetError());
        return -1;
    } 
    enemysSheet.loadFromFile(gRenderer, "assets/spirits/enemys.bmp");
    Sprite enemy1(&enemysSheet, 2);

    enemy1.setFrameClip(0, 0, 0, 50, 50);
    enemy1.setFrameClip(1, 0, 0, 50, 50);
    
    SDL_Event event;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            //Any keypress down
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        rect.x -= playerSpeed;  
                        break;
                    case SDLK_RIGHT:
                        rect.x += playerSpeed;
                }
            }
        }
	// Clear the screen with black
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
        SDL_RenderClear(gRenderer);

        // Set a color for the player rectangle (yellow)
        SDL_SetRenderDrawColor(gRenderer, 255, 255, 0, 255);
        
        // Render the enemy sprite
        enemy1.render(gRenderer);

	SDL_RenderCopy(gRenderer, enemysSheet.getTexture(), NULL, NULL);

        // Render the player rectangle
        SDL_RenderFillRect(gRenderer, &rect);

        // Present the current rendering to the screen
        SDL_RenderPresent(gRenderer);
    }

    close();
    return 0;
}

void loadMedia() {
}

bool init() {
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

    int imgFlags = IMG_INIT_PNG;
    //TODO not used now
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        success = false;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == NULL) {
        printf("Failed to init Window, SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    gScreenSurface = SDL_GetWindowSurface(gWindow); 

    return success;
}

void close() {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    SDL_Quit();
}
