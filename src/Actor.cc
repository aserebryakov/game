#include <stdio.h>
#include "Actor.h"


Actor::Actor(const std::shared_ptr<SpriteResource> resource,
             SDL_Renderer* renderer, int16_t x,
             int16_t y, int16_t vx, int16_t vy) :
  RenderableObject(resource, renderer),
  x_(x),
  y_(y),
  vx_(vx),
  vy_(vy),
  alive_(true),
  shooting_(false) {
  // Set x and y of the sprite
  RenderableObject::set_x(x - rectangle_.w/2);
  RenderableObject::set_y(y - rectangle_.h/2);
}


int16_t Actor::get_x() const {
  return x_;
}


int16_t Actor::get_y() const {
  return y_;
}


void Actor::set_x(int16_t new_x) {
  x_ = new_x;
}


void Actor::set_y(int16_t new_y) {
  y_ = new_y;
}


const SDL_Rect& Actor::get_rectangle() const {
  return rectangle_;
}


int16_t Actor::get_vx() const {
  return vx_;
}


int16_t Actor::get_vy() const {
  return vy_;
}


void Actor::set_vx(int16_t new_vx) {
  vx_ = new_vx;
}


void Actor::set_vy(int16_t new_vy) {
  vy_ = new_vy;
}


void Actor::UpdatePosition() {
  x_ += vx_;
  y_ += vy_;
  RenderableObject::set_x(x_ - (rectangle_.w/2));
  RenderableObject::set_y(y_ - (rectangle_.h/2));
}


bool Actor::Alive() const {
  return alive_;
}


void Actor::Alive(bool value) {
  alive_ = value;
}


bool Actor::Shooting() const {
  return shooting_;
}


void Actor::Shooting(bool value) {
  shooting_ = value;
}
