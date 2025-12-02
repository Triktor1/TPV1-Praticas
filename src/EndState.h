#pragma once
#include "GameState.h"
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
    EndState(SDLApplication* window, bool victory);
    void render() const override; 
    void handleEvent(const SDL_Event& e) override; 
};

