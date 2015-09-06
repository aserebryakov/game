#include "SpriteResource.h"


SpriteResource::SpriteResource(std::string path) {
  surface_ = SDL_LoadBMP(path.c_str());

  if (surface_ == nullptr) {
    throw;
  }

  SDL_SetColorKey(surface_, SDL_TRUE, SDL_MapRGB(surface_->format, 0xFF, 0x00, 0xFF));
}
