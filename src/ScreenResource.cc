#include "ScreenResource.h"


ScreenResource::ScreenResource() : surface_(nullptr) {
}


ScreenResource::~ScreenResource() {
  if (surface_ != nullptr) {
    SDL_FreeSurface(surface_);
  }
}


SDL_Surface* ScreenResource::get_surface() {
  return surface_;
}
