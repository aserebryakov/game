#ifndef PLAYER_H
#define PLAYER_H


#include "Actor.h"


class Player : public Actor {
  public:
    Player(const std::shared_ptr<SpriteResource> resource,
           SDL_Renderer* renderer, int16_t x, int16_t y);

    Player(const Player& other) = delete;
    Player(const Player&& other) = delete;
    virtual ~Player() = default;
    virtual void HandleEvent(const SDL_Event& e);
};

#endif // PLAYER_H
