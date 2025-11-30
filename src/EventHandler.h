#pragma once
#include <SDL3/SDL.h>
class EventHandler
{
public:
   virtual void handleEvent(SDL_Event& e);    
};

