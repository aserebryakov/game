#include "TextResource.h"


TextResource::TextResource(TTF_Font* font, std::string text, SDL_Color text_color) {
  if (font == nullptr) {
    printf("Invalid font pointer passed");
    throw;
  }

  surface_ = TTF_RenderText_Solid(font, text.c_str(), text_color);

  if (surface_ == nullptr) {
    printf("Failed to render text! SDL_ttf Error: %s\n", TTF_GetError());
    throw;
  }
}
