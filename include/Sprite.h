#ifndef SPRITE_H
#define SPRITE_H


#include <memory>
#include <SDL.h>
#include "SpriteResource.h"


class Sprite {
  public:
    Sprite(const std::shared_ptr<SpriteResource> resource,
           SDL_Renderer* renderer);

    Sprite(const Sprite& other) = delete;
    Sprite(const Sprite&& other) = delete;
    virtual ~Sprite();

    void Render(SDL_Renderer* renderer);

    int16_t get_x() const;
    int16_t get_y() const;
    void set_x(int16_t x);
    void set_y(int16_t y);

  protected:
    SDL_Texture* texture_;
    SDL_Rect rectangle_;
};

#endif // SPRITE_H
