#pragma once
#include "gameState.h"
#include "texture.h"
#include <vector>
#include "Button.h"

class PlayState;
class PauseState :
    public GameState
{
private:
    PlayState* playState;
    std::vector<Button*> buttons;
public:
    PauseState(SDLApplication* window, PlayState* previousState, bool paused);
    ~PauseState() override;
     void render() const override;
     void handleEvent(const SDL_Event& e) override;
};

