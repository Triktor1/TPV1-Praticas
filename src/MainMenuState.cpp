#include "MainMenuState.h"
#include <SDL3/SDL.h>
#include <filesystem>
#include "texture.h"
#include "SDLApplication.h"
#include "playState.h"
#include "GameError.h"

constexpr int BUT_Y= 300;
constexpr int SALIRBUT_Y = 370;
constexpr int MAPBUT_X = 250;
constexpr int LEFTBUTX = 10;
constexpr int RIGHTBUTX = 420;
constexpr int BODYX =100;
constexpr int BODYY = 190;
constexpr int BODYZ = 250;
constexpr int BODYW = 30;





MainMenuState::MainMenuState(SDLApplication* window, Texture* bg, Texture* selectMap) :
	GameState(window), bg(bg), selectMap(selectMap)
{
	for (auto& entry : std::filesystem::directory_iterator("../assets/maps")) {
		if (entry.is_regular_file()) {
			mapFiles.push_back(entry.path().string());
		}
	}

	loadConfig();

	for (size_t i = 0; i < mapFiles.size(); i++) {
		Button* b = new Button(this, window->getTexture(SDLApplication::TextureName(window->AVISPADO + i)), game->WINDOW_WIDTH / 2 - game->getTexture(SDLApplication::TextureName(window->AVISPADO + i))->getFrameWidth() / 2, BUT_Y);
		mapButtons.push_back(b);
		buttons.push_back(b);
		addObject(b);
		addEventListener(b);
		b->connect([this, i] {
			game->pushState(std::make_shared<PlayState>(game, mapFiles[i]));
			});
	}

	updateButtons();

	//boton izquierda
	Texture* izTex = window->getTexture(SDLApplication::LEFT);
	Button* leftButton = new Button(this, izTex, LEFTBUTX, BUT_Y);
	leftButton->connect([this]() {
		//mover izq
		previousMap();
		});
	addObject(leftButton);
	addEventListener(leftButton);

	//boton derecha
	Texture* dchaTex = window->getTexture(SDLApplication::RIGHT);
	Button* rightButton = new Button(this, dchaTex, RIGHTBUTX, BUT_Y);
	rightButton->connect([this]() {
		//mover dcha
		nextMap();
		});
	addObject(rightButton);
	addEventListener(rightButton);

	Texture* exitTex = window->getTexture(SDLApplication::SALIR);
	Button* exitButton = new Button(this, exitTex, game->WINDOW_WIDTH / 2 - game->getTexture(game->SALIR)->getFrameWidth() / 2, SALIRBUT_Y);
	exitButton->connect([this]() {
		game->setExit(true);
		});
	addObject(exitButton);
	addEventListener(exitButton);

	buttons.push_back(leftButton);
	buttons.push_back(rightButton);
	buttons.push_back(exitButton);
}

MainMenuState::~MainMenuState() {
	saveConfig();
	for(Button* b : buttons) {
		delete b;
	}
}

void MainMenuState::render() const {

	bg->render();
	if (selectMap) {
		SDL_FRect cuerpo{BODYX,BODYY, BODYZ,BODYW };
		selectMap->render(cuerpo);
	}
	if (!mapButtons.empty()) {
		mapButtons[currentMap]->Render();
	}
	GameState::render();
}

void MainMenuState::handleEvent(const SDL_Event& e) {
	GameState::handleEvent(e);

	if (e.type == SDL_EVENT_KEY_DOWN) {
		switch (e.key.key) {
		case SDLK_LEFT:
			previousMap();
			break;
		case SDLK_RIGHT:
			nextMap();
			break;
		case SDLK_RETURN:
			if (!mapFiles.empty())
				game->pushState(std::make_shared<PlayState>(game, mapFiles[currentMap]));
			break;
		default:
			break;
		}
	}
}

void MainMenuState::nextMap() {
	currentMap++;
	if (currentMap >= mapButtons.size()) currentMap = 0;
	updateButtons();
}

void MainMenuState::previousMap() {
	if (currentMap == 0) {
		currentMap = mapButtons.size() - 1;
	}
	else
		currentMap--;
	updateButtons();
}

void MainMenuState::loadConfig() {
	std::ifstream file(configFile);
	if (!file.is_open()) return;

	std::string lastMap;
	file >> lastMap;
	file.close();

	for (size_t i = 0; i < mapFiles.size(); i++) {
		if (mapFiles[i] == lastMap) {
			currentMap = i;
			break;
		}
	}
}

void MainMenuState::updateButtons() {
	for (size_t i = 0; i < mapButtons.size(); ++i) {
		mapButtons[i]->setActive(i == currentMap);
	}
}

void MainMenuState::saveConfig() {
	std::ofstream file(configFile);
	if (!file.is_open()) return;
	file << mapFiles[currentMap];
	file.close();
}

