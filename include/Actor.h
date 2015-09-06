#ifndef ACTOR_H
#define ACTOR_H


#include "RenderableObject.h"
#include "IEventHandler.h"


class Actor : public RenderableObject, public IEventHandler {
  public:
    Actor(const std::shared_ptr<SpriteResource> resource,
          SDL_Renderer* renderer,
          int16_t x, int16_t y, int16_t vx, int16_t vy);

    Actor(const Actor& other) = delete;
    Actor(const Actor&& other) = delete;
    virtual ~Actor() = default;

    virtual void HandleEvent(const SDL_Event& e) = 0;
    int16_t get_x() const;
    int16_t get_y() const;
    void set_x(int16_t new_x);
    void set_y(int16_t new_y);
    const SDL_Rect& get_rectangle() const;

    int16_t get_vx() const;
    int16_t get_vy() const;
    void set_vx(int16_t new_vx);
    void set_vy(int16_t new_vy);
    void UpdatePosition();

    bool Alive() const;
    void Alive(bool value);

    bool Shooting() const;
    void Shooting(bool value);

  protected:
    int16_t x_;
    int16_t y_;
    int16_t vx_;
    int16_t vy_;
    bool alive_;
    bool shooting_;
};

#endif // ACTOR_H
