#ifndef ENEMY_H
#define ENEMY_H


#include "Actor.h"


class Enemy : public Actor {
  public:
    Enemy(std::string path, SDL_Renderer* renderer,
           int16_t x, int16_t y, int16_t vx, int16_t vy);

    Enemy(const Enemy& other) = delete;
    Enemy(const Enemy&& other) = delete;
    virtual ~Enemy() = default;
    virtual void HandleEvent(const SDL_Event& e);
};

#endif // ENEMY_H
