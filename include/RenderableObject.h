#ifndef RENDERABLE_OBJECT_H
#define RENDERABLE_OBJECT_H

#include "Sprite.h"

class RenderableObject : public Sprite {
  public:
    RenderableObject(const std::shared_ptr<SpriteResource> resource,
                     SDL_Renderer* renderer);

    RenderableObject(const RenderableObject& other) = delete;
    RenderableObject(const RenderableObject&& other) = delete;
    virtual ~RenderableObject() = default;
};

#endif // RENDERABLE_OBJECT_H
