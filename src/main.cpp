#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#define SCREEN_HEIGHT 720
#define SCREEN_WIDTH 1280

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Renderer* gRenderer = NULL;
int playerSpeed = 5;

enum SpritesTextures {
    PLAYER,
    ENEMY1,
};

class LTexture {
    public:
        //init
        LTexture();
        //deallocate
        ~LTexture();

        //Load image
        bool loadFromFile( std::string path );
        //deallocate texture
        void free();
        //render texture at a specific SDL_Rect
        void render(int x, int y, SDL_Rect* clip = NULL);

        int getWidth();
        int getHeight();

    private:
        SDL_Texture* mTexture;

        int mWidth;
        int mHeight;
};

LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

void LTexture::free() {
    if (mTexture == NULL) {
        return;
    }
    SDL_DestroyTexture(mTexture);
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

void LTexture::render(int x, int y, SDL_Rect* clip) {
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};

    if (clip != NULL) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

bool LTexture::loadFromFile(std::string path) {
    free();

    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
    if (loadedSurface == NULL) {
        printf("Unable to load BMP %s, SDL Error: %s\n", path.c_str(),SDL_GetError());
    }

    newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    if (newTexture == NULL) {
        printf("Unable to create Texture from %s, SDL Error: %s\n", path.c_str(), SDL_GetError());
    }
    mWidth = loadedSurface->w;
    mHeight = loadedSurface->h;
    
    SDL_FreeSurface(loadedSurface);
    
    mTexture = newTexture;
    return mTexture != NULL;
}


SDL_Rect gSpriteClips[2];
LTexture gSpriteSheetTexture;

SDL_Rect rect = {SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100, 50, 50};

void close();
bool init();

int main(int argc, char* args[]) {
    if(!init()) {
        printf("Failed to init! SDL_Error: %s\n", SDL_GetError());
        return -1;
    } 

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

        
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
        SDL_RenderClear(gRenderer);
        SDL_SetRenderDrawColor(gRenderer, 255, 255, 0, 255);

        SDL_RenderFillRect(gRenderer, &rect);

        SDL_RenderPresent(gRenderer);
    }

    close();
    return 0;
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

