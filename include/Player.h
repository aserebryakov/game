#ifndef PLAYER_H
#define PLAYER_H


#include "RenderableObject.h"
#include "IEventHandler.h"


class Player : public RenderableObject, public IEventHandler {
  public:
    Player(std::string path, SDL_Renderer* renderer);
    Player(const Player& other) = delete;
    Player(const Player&& other) = delete;
    virtual ~Player() = default;
    virtual void HandleEvent(const SDL_Event& e);
};

#endif // PLAYER_H
