#include "RenderableObject.h"

RenderableObject::RenderableObject(const std::shared_ptr<SpriteResource> resource,
                                   SDL_Renderer* renderer) :
                                   Sprite(resource, renderer) {
}

