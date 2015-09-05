#ifndef BULLET_H
#define BULLET_H


#include "Actor.h"


class Bullet : public Actor {
  public:
    Bullet(std::string path, SDL_Renderer* renderer,
           int16_t x, int16_t y, int16_t vx, int16_t vy);

    Bullet(const Bullet& other) = delete;
    Bullet(const Bullet&& other) = delete;
    virtual ~Bullet() = default;
    virtual void HandleEvent(const SDL_Event& e);
};

#endif // ENEMY_H
