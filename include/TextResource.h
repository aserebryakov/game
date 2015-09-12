#ifndef TEXT_RESOURCE_H
#define TEXT_RESOURCE_H


#include <string>
#include <SDL_ttf.h>
#include "ScreenResource.h"


class TextResource : public ScreenResource {
  public:
    TextResource(TTF_Font* font, std::string text, SDL_Color text_color);

    TextResource(const TextResource& other) = delete;
    TextResource(const TextResource&& other) = delete;
    virtual ~TextResource() = default;
};

#endif // TEXT_RESOURCE_H
