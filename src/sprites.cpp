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
    mTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);
  }
  
    private:
        SDL_Texture* mTexture;
};

class Sprite {
  LTexture* sSheet;
  SDL_Rect* frames;
  int framesSize;

  Sprite(int size)
    : framesSize(size) {
    frames = new SDL_Rect[size];
  }
  ~Sprite() {
    delete []frames;
  }

  void render(SDl_renderer* renderer){
    for (int i = 0; i < framesSize; i++) {
      renderFrame(renderer, i);x
    }
  }
  void renderFrame(SDL_Renderer* renderer, int frameIdx) {
    if (frameIdx > framesSize - 1) {
      printf("Frame index is out of reach!");
      return; 
    }
    SDL_RenderCopy(renderer, sSheet.mTexture, NULL, &frames[frameIdx]);
  }

   void freeLTexture(LTexture* texture) {
    if (texture != NULL) {
      SDL_DestroyTexture(texture);
    }
  }
};

