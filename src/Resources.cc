#include "Resources.h"


std::map<std::string, std::shared_ptr<SpriteResource>> Resources::Sprites;
std::map<std::string, TTF_Font*> Resources::Fonts;


void Resources::Initialize() {
  Resources::Sprites["PLAYER"] =
    std::make_shared<SpriteResource>("resources/Player.BMP");
  Resources::Sprites["ENEMY"] =
    std::make_shared<SpriteResource>("resources/Enemy.BMP");
  Resources::Sprites["BULLET"] =
    std::make_shared<SpriteResource>("resources/Bullet.BMP");
  Resources::Sprites["BACKGROUND"] =
    std::make_shared<SpriteResource>("resources/background.BMP"),

  Resources::Fonts["SCORE"] =
    TTF_OpenFont("resources/fonts/minotaur.ttf", 26);
}
