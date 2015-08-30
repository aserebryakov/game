#ifndef SPRITE_H
#define SPRITE_H


#include <string>
#include <SDL.h>


class Sprite {
  public:
    Sprite(std::string path, SDL_Surface* screen_surface);
    Sprite(const Sprite& other) = delete;
    Sprite(const Sprite&& other) = delete;
    ~Sprite();

    void Blit(SDL_Surface* surface);

    uint16_t get_x() const;
    uint16_t get_y() const;
    void set_x(uint16_t x);
    void set_y(uint16_t y);

  private:
    SDL_Surface* sprite_surface_;
    SDL_Rect rectangle_;
};

#endif // SPRITE_H
