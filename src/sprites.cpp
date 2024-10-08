#include <SDL2/SDL.h>

#include <string>

class LTexture {
    public:
  LTexture(){
    mTexture = NULL;
  }
  
  ~LTexture() {
    if (mTexture != NULL) {
      SDL_DestroyTexture(mTexture);
    }
  }
  
  void loadFromFile(SDL_Renderer* renderer, std::string path ) {
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
    if (!loadedSurface) {
      printf("Failed to load surface, SDL ERROR: %s\n", SDL_GetError());
    }
    mTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (!mTexture) {
      printf("Failed to load texture from surface, SDL ERROR: %s\n", SDL_GetError());
    }
    SDL_FreeSurface(loadedSurface);
  }

  SDL_Texture* getTexture() {
    return mTexture;
  }
  
    private:
        SDL_Texture* mTexture;
};

class Sprite {
public:
  int framesSize;
  Sprite(LTexture* spriteSheet, int size)
    : sSheet(spriteSheet),
      framesSize(size) {
    frames = new SDL_Rect[size];
  }

  ~Sprite() {
    delete[] frames;
  }

  void render(SDL_Renderer* renderer) {
    for (int i = 0; i < framesSize; i++) {
      renderFrame(renderer, i);
    }
  }

  void setFrameClip(int frameIdx, int x, int y, int w, int h) {
    if (frameIdx >= framesSize) {  // Correct bounds check
      printf("Frame index is out of reach!\n");
      return;
    }
    frames[frameIdx].x = x;
    frames[frameIdx].y = y;
    frames[frameIdx].w = w;
    frames[frameIdx].h = h;
  }

  void renderFrame(SDL_Renderer* renderer, int frameIdx) {
    if (frameIdx >= framesSize) {  // Correct bounds check
      printf("Frame index is out of reach!\n");
      return;
    }
    if (SDL_RenderCopy(renderer, sSheet->getTexture(), NULL, &frames[frameIdx]) != 0) {
      printf("Failed to render frame: %s\n", SDL_GetError());
    }
  }

  void freeLTexture(LTexture* texture) {
    if (texture != NULL) {
      SDL_DestroyTexture(texture->getTexture());
    }
  }

private:
  LTexture* sSheet;
  SDL_Rect* frames;
};

