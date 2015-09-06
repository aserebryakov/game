#include "Bullet.h"


Bullet::Bullet(const std::shared_ptr<SpriteResource> resource,
               SDL_Renderer* renderer,
               int16_t x, int16_t y, int16_t vx, int16_t vy) :
               Actor(resource, renderer, x, y, vx, vy) {
}


void Bullet::HandleEvent(const SDL_Event& e) {
}
