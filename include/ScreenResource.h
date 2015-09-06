#ifndef SCREEN_RESOURCE_H
#define SCREEN_RESOURCE_H


#include <SDL.h>


class ScreenResource {
  public:
    ScreenResource();
    ScreenResource(const ScreenResource& other) = delete;
    ScreenResource(const ScreenResource&& other) = delete;
    virtual ~ScreenResource();
    SDL_Surface* get_surface();

  protected:
    SDL_Surface* surface_;
};

#endif // SCREEN_RESOURCE_H
