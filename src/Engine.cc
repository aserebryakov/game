#include <stdio.h>
#include "Engine.h"
#include "Sprite.h"


const uint16_t Engine::kScreenWidth = 640;
const uint16_t Engine::kScreenHeight = 480;


Engine::Engine() : game_window_(nullptr), screen_surface_(nullptr) {
}


Engine::~Engine() {
  //Destroy window
  SDL_DestroyWindow(game_window_);
  SDL_Quit();
}


void Engine::Init() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    throw;
  }

  //Create window
  game_window_ = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED, kScreenWidth,
                                  kScreenHeight, SDL_WINDOW_SHOWN);
  if (game_window_ == nullptr)
  {
    printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
    throw;
  }

  //Get window surface
  screen_surface_ = SDL_GetWindowSurface(game_window_);

  //Fill the surface white
  SDL_FillRect(screen_surface_, nullptr,
               SDL_MapRGB(screen_surface_->format, 0xFF, 0x00, 0xFF));

  //Update the surface
  SDL_UpdateWindowSurface(game_window_);
}


void Engine::Main() {
  Sprite background("resources/background.BMP", screen_surface_);
  Sprite player("resources/Player.BMP", screen_surface_);
  SDL_Event e;
  bool quit = false;

  player.set_x(kScreenWidth / 2);
  player.set_y(kScreenHeight / 2);

  while (quit != true) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        quit = true;
        break;
      }

      if (e.type == SDL_KEYDOWN)
      {
        switch (e.key.keysym.sym) {
          case SDLK_UP: {
            player.set_y(player.get_y() - 1);
            break;
          }
          case SDLK_DOWN: {
            player.set_y(player.get_y() + 1);
            break;
          }
          case SDLK_RIGHT: {
            player.set_x(player.get_x() + 1);
            break;
          }
          case SDLK_LEFT: {
            player.set_x(player.get_x() - 1);
            break;
          }
        }
      }
    }

    background.Blit(screen_surface_);
    player.Blit(screen_surface_);
    SDL_UpdateWindowSurface(game_window_);
  }
}


uint16_t Engine::get_screen_width() const {
  return kScreenWidth;
}


uint16_t Engine::get_screen_height() const {
  return kScreenHeight;
}


SDL_Surface* Engine::get_screen_surface() const {
  return screen_surface_;
}

