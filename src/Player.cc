#include <stdio.h>
#include "Player.h"


Player::Player(const std::shared_ptr<ScreenResource> resource,
               SDL_Renderer* renderer,
               int16_t x, int16_t y) :
  Actor(resource, renderer, x, y, 0, 0) {
}


void Player::HandleEvent(const SDL_Event& e) {
  if (e.type == SDL_KEYDOWN) {
    switch (e.key.keysym.sym) {
      case SDLK_UP: {
        set_vy(get_vy() - 1);
        break;
      }
      case SDLK_DOWN: {
        set_vy(get_vy() + 1);
        break;
      }
      case SDLK_RIGHT: {
        set_vx(get_vx() + 1);
        break;
      }
      case SDLK_LEFT: {
        set_vx(get_vx() - 1);
        break;
      }
      case SDLK_SPACE: {
        shooting_ = true;
        break;
      }
    }
  }
}
