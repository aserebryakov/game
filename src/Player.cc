#include <stdio.h>
#include "Player.h"

Player::Player(std::string path, SDL_Renderer* renderer,
               int16_t x, int16_t y) :
  Actor(path, renderer, x, y, 0, 0) {
}


void Player::HandleEvent(const SDL_Event& e) {
  if (e.type == SDL_KEYDOWN) {
    switch (e.key.keysym.sym) {
      case SDLK_UP: {
        set_y(get_y() - 1);
        break;
      }
      case SDLK_DOWN: {
        set_y(get_y() + 1);
        break;
      }
      case SDLK_RIGHT: {
        set_x(get_x() + 1);
        break;
      }
      case SDLK_LEFT: {
        set_x(get_x() - 1);
        break;
      }
    }
  }
}
