#ifndef ENGINE_H
#define ENGINE_H

#include <SDL.h>

class Engine {
  public:
    Engine();
    Engine(const Engine&) = delete;
    ~Engine();

    void Init();

  private:
    static const uint16_t kScreenWidth;
    static const uint16_t kScreenHeight;
    SDL_Window* game_window_;
    SDL_Surface* screen_surface_;
};

#endif // ENGINE_H
