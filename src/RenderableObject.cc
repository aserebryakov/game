#include "RenderableObject.h"

RenderableObject::RenderableObject(const std::shared_ptr<ScreenResource> resource,
                                   SDL_Renderer* renderer) :
                                   Sprite(resource, renderer) {
}

