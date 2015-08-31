#include "Sprite.h"


Sprite::Sprite(std::string path, SDL_Renderer* renderer) : texture_(nullptr) {
  SDL_Surface* temp_surface = SDL_LoadBMP(path.c_str());

  if (temp_surface == nullptr) {
    throw;
  }

  texture_ = SDL_CreateTextureFromSurface(renderer, temp_surface);

  if (texture_ == nullptr) {
    throw;
  }

  SDL_FreeSurface(temp_surface);
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


uint16_t Sprite::get_x() const {
  return rectangle_.x;
}


uint16_t Sprite::get_y() const {
  return rectangle_.y;
}


void Sprite::set_x(uint16_t x) {
  rectangle_.x = x;
}


void Sprite::set_y(uint16_t y) {
  rectangle_.y = y;
}
