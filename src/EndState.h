#pragma once
#include "gameState.h"
#include <SDL3/SDL.h>
#include "texture.h"
#include <vector>
#include "Button.h"

class PlayState;
class EndState :
    public GameState
{
private: 
    PlayState* playState; 
    bool victory; 
    Texture* resultTexture;
	std::vector<Button*> buttons;

public: 
    EndState(SDLApplication* window, bool victory);
    ~EndState() override;
    void render() const override; 
    void handleEvent(const SDL_Event& e) override; 
};

