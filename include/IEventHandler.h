#ifndef I_EVENT_HANDLER_H
#define I_EVENT_HANDLER_H


#include <SDL.h>


class IEventHandler {
  public:
    virtual void HandleEvent(const SDL_Event& e) = 0;
};

#endif // I_EVENT_HANDLER_H
