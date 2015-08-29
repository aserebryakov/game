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
  Sprite sp("resources/background.BMP", screen_surface_);

  sp.Blit(screen_surface_);
  SDL_UpdateWindowSurface(game_window_);

  SDL_Delay(2000);
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

