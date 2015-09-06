#ifndef SPRITE_RESOURCE_H
#define SPRITE_RESOURCE_H


#include <string>
#include "ScreenResource.h"


class SpriteResource : public ScreenResource {
  public:
    SpriteResource(std::string path);

    SpriteResource(const SpriteResource& other) = delete;
    SpriteResource(const SpriteResource&& other) = delete;
    virtual ~SpriteResource() = default;
};

#endif // SPRITE_RESOURCE_H
