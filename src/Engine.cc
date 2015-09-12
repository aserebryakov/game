#include <stdio.h>
#include <vector>
#include <random>
#include "Engine.h"
#include "Sprite.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "SDL_ttf.h"
#include "TextResource.h"
#include "Resources.h"


const uint16_t Engine::kScreenWidth = 640;
const uint16_t Engine::kScreenHeight = 480;


Engine::Engine() : game_window_(nullptr), screen_surface_(nullptr),
  renderer_(nullptr), score_(0), quit_(false), player_(nullptr) {
}


Engine::~Engine() {
  //Destroy window
  SDL_DestroyWindow(game_window_);
  SDL_DestroyRenderer(renderer_);
  TTF_Quit();
  SDL_Quit();
}


void Engine::Init() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    throw;
  }

  if (TTF_Init() < 0)
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

  Resources::Initialize();
}


void Engine::Main() {
  while (quit_ == false) {
    InitializeScene();
    GameLoop();
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
  acting_objects_.clear();
  static_objects_.clear();
  event_handlers_.clear();
  new_objects_.clear();

  static_objects_.push_back(std::make_shared<RenderableObject>(
                              Resources::Sprites["BACKGROUND"],
                              renderer_));
  SpawnPlayer();
}


void Engine::GameLoop() {
  SDL_Event e;
  bool stop = false;

  while (stop != true) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT ||
          (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
        stop = true;
        quit_ = true;
        break;
      }

      for (auto& handler : event_handlers_) {
        handler->HandleEvent(e);
      }
    }

    UpdateScene();
    RenderScene();
    SDL_Delay(20);

    if (player_->Alive() == false) {
      stop = true;
    }
  }
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

  RenderHUD();

  SDL_RenderPresent(renderer_);
}


void Engine::RenderHUD() {
  SDL_Color text_color = {0xff, 0xff, 0xff};
  score_text_ = std::make_shared<RenderableObject>(
                  std::make_shared<TextResource>(
                    Resources::Fonts["SCORE"],
                    std::to_string(score_),
                    text_color),
                  renderer_);

  score_text_->Render(renderer_);
}


void Engine::SpawnPlayer() {
  player_ = std::make_shared<Player>(Resources::Sprites["PLAYER"],
                                     renderer_,
                                     kScreenWidth / 2, 3 * kScreenHeight / 4);
  SpawnObject(player_);
  event_handlers_.push_back(player_);
}


void Engine::SpawnEnemy() {
  static std::random_device rd;
  static std::default_random_engine e(rd());
  static std::uniform_int_distribution<int> probability(1, 20);
  static std::uniform_int_distribution<int> position(0, kScreenWidth);

  if (probability(e) == 1) {
    auto enemy = std::make_shared<Enemy>(Resources::Sprites["ENEMY"],
                                         renderer_,
                                         position(e), 0, 0, 5);
    SpawnObject(enemy);
  }
}


void Engine::SpawnBullets() {
  for (auto& object : acting_objects_) {
    if (object->Shooting() == true) {
      try {
        SDL_Rect r = object->get_rectangle();
        SpawnObject(std::make_shared<Bullet>(Resources::Sprites["BULLET"],
                    renderer_, object->get_x(),
                    object->get_y() - r.h / 2 - 10, 0, -10));

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
        score_ += 10;
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
