#pragma once
#include "gameState.h"
#include "texture.h"
#include "Button.h"
#include <vector>
class PlayState;
class MainMenuState :
    public GameState
{
private:
  PlayState* playState;
  Texture* bg;
  Texture* selectMap;

  //vector de botones de mapas
  int currentMap = 0; 
  std::vector<Button*> mapButtons;

public:
    MainMenuState(SDLApplication* window, PlayState* previousState, Texture* bg, Texture* selectMap);
   void render() const override;
   void handleEvent(const SDL_Event& e) override;

   //para la cambiar entre mapas
   void nextMap();
   void previousMap();
};

