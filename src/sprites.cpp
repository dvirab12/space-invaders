#include <SDL2/SDL.h>

enum spriteID {
  ENEMY1,
  ENEMY2,
  ENEMY3,
};

class Sprite {
  SDL_Texture* sSheet;
  SDL_Rect* frames;
  int framesSize;

  Sprite(int size)
    : framesSize(size) {
    frames = new SDL_Rect[size];
  }
  ~Sprite() {
    delete []frames;
  }

  void render(SDL_Renderer* renderer, int frameIdx) {
    if (frameIdx > framesSize - 1) {
      printf("Frame index is out of reach!");
      return; 
    }
    SDL_RenderCopy(renderer, sSheet, NULL, &frames[frameIdx]);
  }

  void freeTexture(SDL_Texture* texture) {
    if (texture != NULL) {
      SDL_DestroyTexture(texture);
    }
  }
};

