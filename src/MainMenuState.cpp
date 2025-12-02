#include "MainMenuState.h"
#include <SDL3/SDL.h>
#include <filesystem>
#include "texture.h"
#include "SDLApplication.h"
#include "playState.h"
#include "GameError.h"


MainMenuState::MainMenuState(SDLApplication* window, Texture* bg, Texture* selectMap) :
	GameState(window), bg(bg), selectMap(selectMap)
{
	for (auto& entry : std::filesystem::directory_iterator("../assets/maps")) {
		if (entry.is_regular_file()) {
			mapFiles.push_back(entry.path().stem().string());
		}
		else {
			throw FileNotFoundError(entry.path().string());
		}
	}

	loadConfig();

	for (size_t i = 0; i < mapFiles.size(); i++) {
		Button* b = new Button(this, window->getTexture(SDLApplication::TextureName(window->AVISPADO + i)), 100, 250);
		mapButtons.push_back(b);
		addObject(b);
		addEventListener(b);
		b->connect([this, i] {
			game->pushState(new PlayState(game, mapFiles[i]));
			});
	}

	//boton izquierda
	Texture* izTex = window->getTexture(SDLApplication::LEFT);
	Button* leftButton = new Button(this, izTex, 200, 350);
	leftButton->connect([this]() {
		//mover izq
		previousMap();
		});
	addObject(leftButton);
	addEventListener(leftButton);

	//boton derecha
	Texture* dchaTex = window->getTexture(SDLApplication::RIGHT);
	Button* rightButton = new Button(this, dchaTex, 200, 450);
	rightButton->connect([this]() {
		//mover dcha
		nextMap();
		});
	addObject(rightButton);
	addEventListener(rightButton);

	Texture* exitTex = window->getTexture(SDLApplication::SALIR);
	Button* exitButton = new Button(this, exitTex, 150, 150);
	exitButton->connect([this]() {
		game->popState();
		});
	addObject(exitButton);
	addEventListener(exitButton);
}

MainMenuState::~MainMenuState() {
	saveConfig();
	std::cout << "prueba";
	for (Button* b : mapButtons) {
		delete b;
	}
}

void MainMenuState::render() const {
	SDL_Renderer* renderer = game->getRenderer();
	SDL_RenderClear(renderer);
	if (bg) bg->render();
	if (selectMap) {
		SDL_FRect cuerpo{ 100,190,250,30 };
		selectMap->render(cuerpo);
	}
	if (!mapButtons.empty()) {
		mapButtons[currentMap]->Render();
	}

	GameState::render();
	SDL_RenderPresent(renderer);
}

void MainMenuState::handleEvent(const SDL_Event& e) {
	GameState::handleEvent(e);
	if (!mapButtons.empty())
		mapButtons[currentMap]->handleEvent(e);

	if (e.type == SDL_EVENT_KEY_DOWN) {
		switch (e.key.key) {
		case SDLK_LEFT:
			previousMap();
			break;
		case SDLK_RIGHT:
			nextMap();
			break;
		case SDLK_RETURN:
		case SDLK_KP_ENTER:
			if (!mapFiles.empty())
				game->pushState(new PlayState(game, mapFiles[currentMap]));
			break;
		default:
			break;
		}
	}
}

void MainMenuState::nextMap() {
	currentMap++;
	if (currentMap >= mapButtons.size()) currentMap = 0;
}

void MainMenuState::previousMap() {
	if (currentMap == 0) {
		currentMap = mapButtons.size() - 1;
	}
	else currentMap--;
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
		mapButtons[i]->setActive(i == currentMap); // comparación natural
	}
}

void MainMenuState::saveConfig() {
	std::ofstream file(configFile);
	if (!file.is_open()) return;
	file << mapFiles[currentMap];
	file.close();
}

