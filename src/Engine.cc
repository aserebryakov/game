#include <stdio.h>
#include <vector>
#include <random>
#include "Engine.h"
#include "Sprite.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"


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
  game_window_ = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED,
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
      if (e.type == SDL_QUIT ||
          (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
        quit = true;
        break;
      }

      for (auto& handler : event_handlers_) {
        handler->HandleEvent(e);
      }
    }

    UpdateScene();
    RenderScene();
    SDL_Delay(20);
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
  static_objects_.push_back(std::make_shared<RenderableObject>("resources/background.BMP", renderer_));
  SpawnPlayer();
}


void Engine::UpdateScene() {
  for (auto& object : acting_objects_) {
    object->UpdatePosition();
  }

  for (auto& object : new_objects_) {
    acting_objects_.push_back(object);
    object->UpdatePosition();
  }

  new_objects_.clear();

  SpawnEnemy();
  SpawnBullets();
  DetectCollisions();
  CleanupScene();
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


void Engine::SpawnPlayer() {
  auto player = std::make_shared<Player>("resources/Player.BMP", renderer_,
                                         kScreenWidth / 2, 3 * kScreenHeight / 4);
  SpawnObject(player);
  event_handlers_.push_back(player);
}


void Engine::SpawnEnemy() {
  static std::random_device rd;
  static std::default_random_engine e(rd());
  static std::uniform_int_distribution<int> probability(1, 20);
  static std::uniform_int_distribution<int> position(0, kScreenWidth);

  if (probability(e) == 1) {
    auto enemy = std::make_shared<Enemy>("resources/Enemy.BMP", renderer_,
                                          position(e), 0, 0, 5);
    SpawnObject(enemy);
  }
}


void Engine::SpawnBullets() {
  for (auto& object : acting_objects_) {
    if (object->Shooting() == true) {
      try {
        SDL_Rect r = object->get_rectangle();
        SpawnObject(std::make_shared<Bullet>("resources/Bullet.BMP", renderer_,
          object->get_x(), object->get_y() - r.h / 2 - 10, 0, -10));
        object->Shooting(false);
      } catch (...) {
        printf("Could not spawn bullet! SDL_Error: %s\n", SDL_GetError());
      }
    }
  }
}


void Engine::SpawnObject(std::shared_ptr<Actor> object) {
  new_objects_.push_back(object);
}


void Engine::DetectCollisions() {
  size_t objects_number = acting_objects_.size();
  size_t index = 0;
  SDL_Rect intersect_dummy;

  while (index < objects_number) {
    for (size_t i = index + 1; i < objects_number; i++) {
      if (SDL_IntersectRect(&(acting_objects_[index]->get_rectangle()),
         &(acting_objects_[i]->get_rectangle()), &intersect_dummy) == true) {
        acting_objects_[index]->Alive(false);
        acting_objects_[i]->Alive(false);
      }
    }
    index++;
  }
}


void Engine::CleanupScene() {
  std::vector<std::shared_ptr<Actor>> left_objects;

  for (auto& object : acting_objects_) {
    if (object->Alive() == true) {
      if (object->get_rectangle().y <= kScreenHeight) {
        left_objects.push_back(object);
      }
    }
  }

  acting_objects_ = left_objects;
}
