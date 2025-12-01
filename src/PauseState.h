#pragma once
#include "gameState.h"
#include "texture.h"

class PlayState;
class PauseState :
    public GameState
{
private:
    PlayState* playState;
    Texture* resultTexture;
public:
    PauseState(SDLApplication* window, PlayState* previousState, bool paused);
     void render() const override;
     void handleEvent(const SDL_Event& e) override;
};

