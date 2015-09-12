#include "Sprite.h"


Sprite::Sprite(const std::shared_ptr<ScreenResource> resource,
               SDL_Renderer* renderer) : texture_(nullptr),
               resource_(resource) {
  UpdateResource(renderer);

  rectangle_.x = 0;
  rectangle_.y = 0;
}


Sprite::~Sprite() {
  SDL_DestroyTexture(texture_);
}


void Sprite::UpdateResource(SDL_Renderer* renderer) {
  if (resource_->get_surface() == nullptr) {
    printf("Resource is not initialized!\n");
    throw;
  }

  texture_ = SDL_CreateTextureFromSurface(renderer, resource_->get_surface());

  if (texture_ == nullptr) {
    printf("Failed to create texture %s!\n", SDL_GetError());
    throw;
  }

  SDL_QueryTexture(texture_, nullptr, nullptr, &rectangle_.w, &rectangle_.h);
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
