#pragma once
#include "gameState.h"
#include "texture.h"
#include "Button.h"
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>

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
  std::vector<Button*> buttons;
  std::vector<std::string> mapFiles;

  const std::string configFile = "config.txt";

  void loadConfig();
  void saveConfig();
  void updateButtons();

public:
   MainMenuState(SDLApplication* window, Texture* bg, Texture* selectMap);
   ~MainMenuState();

   void render() const override;
   void handleEvent(const SDL_Event& e) override;

   //para la cambiar entre mapas
   void nextMap();
   void previousMap();
};

