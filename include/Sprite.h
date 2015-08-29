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

  private:
    SDL_Surface* sprite_surface_;
    SDL_Rect rectangle_;
};

#endif // SPRITE_H
