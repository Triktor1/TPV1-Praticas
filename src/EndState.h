#pragma once
#include "gameState.h"
#include <SDL3/SDL.h>
#include "texture.h"

class PlayState;
class EndState :
    public GameState
{
private: 
    PlayState* playState; 
    bool victory; 
    Texture* resultTexture;
public: 
    EndState(SDLApplication* window, PlayState* previousState, bool victory);
    virtual void render() const override; 
    virtual void handleEvent(const SDL_Event& e) override; 
};

