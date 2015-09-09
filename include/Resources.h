#ifndef RESOURCES_H
#define RESOURCES_H


#include <map>
#include <string>
#include <memory>
#include <SDL.h>
#include <SDL_ttf.h>
#include "SpriteResource.h"


class Resources {
  public:
    static std::map<std::string, std::shared_ptr<SpriteResource>> Sprites;
    static std::map<std::string, TTF_Font*> Fonts;
    static void Initialize();
};

#endif
