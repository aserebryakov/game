#include "TextResource.h"
#include "SDL_ttf.h"


TextResource::TextResource(std::string text, SDL_Color text_color) {
  TTF_Font* fnt = TTF_OpenFont("resources/fonts/minotaur.ttf", 26);

  if (fnt == nullptr) {
    printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
    throw;
  }

  surface_ = TTF_RenderText_Solid(fnt, text.c_str(), text_color);

  if (surface_ == nullptr) {
    printf("Failed to render text! SDL_ttf Error: %s\n", TTF_GetError());
    throw;
  }
}
