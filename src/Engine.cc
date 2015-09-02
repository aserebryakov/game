#include <stdio.h>
#include <vector>
#include "Engine.h"
#include "Sprite.h"
#include "Player.h"


const uint16_t Engine::kScreenWidth = 640;
const uint16_t Engine::kScreenHeight = 480;


Engine::Engine() : game_window_(nullptr), screen_surface_(nullptr) {
}


Engine::~Engine() {
  //Destroy window
  SDL_DestroyWindow(game_window_);
  SDL_DestroyRenderer(renderer_);
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
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    throw;
  }

  InitializeRenderer();

  SDL_SetRenderDrawColor(renderer_, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderPresent(renderer_);
}


void Engine::Main() {
  SDL_Event e;
  bool quit = false;

  InitializeScene();

  while (quit != true) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        quit = true;
        break;
      }

      for (auto& handler : event_handlers_) {
        handler->HandleEvent(e);
      }
    }

    UpdateScene();
    RenderScene();
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


void Engine::InitializeRenderer() {
  std::vector<SDL_RendererFlags> renderer_modes = {SDL_RENDERER_ACCELERATED,
                                                   SDL_RENDERER_SOFTWARE};

  for (auto mode : renderer_modes) {
    renderer_ = SDL_CreateRenderer(game_window_, -1, mode);

    if (renderer_ != nullptr) {
      return;
    }

    printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
  }

  throw;
}


void Engine::InitializeScene() {
  auto player = std::make_shared<Player>("resources/Player.BMP", renderer_,
                                         kScreenWidth / 2, kScreenHeight / 2);

  acting_objects_.push_back(player);
  static_objects_.push_back(std::make_shared<RenderableObject>("resources/background.BMP", renderer_));
  event_handlers_.push_back(std::dynamic_pointer_cast<IEventHandler>(player));
}


void Engine::UpdateScene() {
  for (auto& object : acting_objects_) {
    object->UpdatePosition();
  }
}


void Engine::RenderScene() {
  for (auto& object : static_objects_) {
    object->Render(renderer_);
  }

  for (auto& object : acting_objects_) {
    object->Render(renderer_);
  }

  SDL_RenderPresent(renderer_);
}
