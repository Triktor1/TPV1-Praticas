#include "MainMenuState.h"
#include <SDL3/SDL.h>
#include "texture.h"
#include "SDLApplication.h"
#include "playState.h"


MainMenuState::MainMenuState(SDLApplication* window, PlayState* previousState, Texture* bg, Texture* selectMap):
    GameState(window), playState(previousState), bg(bg), selectMap(selectMap)
{
    // 5 botones en el mismo sitio
	Button* bOriginal = new Button(this, window->getTexture(SDLApplication::ORIGINAL), 100, 250);
	Button* bPractica1 = new Button(this, window->getTexture(SDLApplication::PRACTICA1), 100, 250);
	Button* bTrivial = new Button(this, window->getTexture(SDLApplication::TRIVIAL), 100, 250);
	Button* bVeloz = new Button(this, window->getTexture(SDLApplication::VELOZ), 100, 250);
	Button* bAvispado = new Button(this, window->getTexture(SDLApplication::AVISPADO), 100, 250);

	mapButtons = { bOriginal, bPractica1, bTrivial, bVeloz, bAvispado};
	mapFiles = {
		"assets/maps/Original.txt",
		"assets/maps/Practica1.txt",
		"assets/maps/Trivial.txt",
		"assets/maps/Veloz.txt",
		"assets/maps/Avispado.txt"
	};

	for (int i = 0; i < mapButtons.size();i++) {
		Button* b = mapButtons[i];
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
		//salir
		});
	addObject(exitButton);
	addEventListener(exitButton);
	}

void MainMenuState::render() const {
	SDL_Renderer* renderer = game->getRenderer();
	SDL_RenderClear(renderer);
	if (bg) bg->render();
	if (selectMap) {
		SDL_FRect cuerpo{ 100,190,250,30 };
		selectMap->render(cuerpo);
	}
	GameState::render();
	SDL_RenderPresent(renderer);
}

void MainMenuState::handleEvent(const SDL_Event& e) {
	GameState::handleEvent(e);
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

