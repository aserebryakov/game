#include "Sprite.h"


Sprite::Sprite(const std::shared_ptr<ScreenResource> resource,
               SDL_Renderer* renderer) : texture_(nullptr) {
  if (resource->get_surface() == nullptr) {
    throw;
  }

  texture_ = SDL_CreateTextureFromSurface(renderer, resource->get_surface());

  if (texture_ == nullptr) {
    throw;
  }

  SDL_QueryTexture(texture_, nullptr, nullptr, &rectangle_.w, &rectangle_.h);

  rectangle_.x = 0;
  rectangle_.y = 0;
}


Sprite::~Sprite() {
  SDL_DestroyTexture(texture_);
}


void Sprite::Render(SDL_Renderer* renderer) {
  SDL_RenderCopy(renderer, texture_, nullptr, &rectangle_);
}


int16_t Sprite::get_x() const {
  return rectangle_.x;
}


int16_t Sprite::get_y() const {
  return rectangle_.y;
}


void Sprite::set_x(int16_t x) {
  rectangle_.x = x;
}


void Sprite::set_y(int16_t y) {
  rectangle_.y = y;
}
