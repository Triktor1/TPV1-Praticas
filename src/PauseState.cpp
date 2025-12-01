#include "PauseState.h"
#include "playState.h"
#include "Button.h"
#include "MainMenuState.h"
#include "SDLApplication.h"
#include <SDL3/SDL.h>

PauseState::PauseState(SDLApplication* window, PlayState* previousState, bool paused) :
	GameState(window), playState(previousState)
{

	//boton continuar
	Texture* continueTex = window->getTexture(SDLApplication::CONTINUAR);
	Button* continueButton = new Button(this, continueTex, 200, 350);
	continueButton->connect([this]() {
		//continuar
		game->popState();
		});
	addObject(continueButton);
	addEventListener(continueButton);


	//boton Reiniciar
	Texture* restartTex = window->getTexture(SDLApplication::REINICIAR);
	Button* restartButton = new Button(this, restartTex, 200, 450);
	restartButton->connect([this]() {
		//reinicio
		playState->destroySceneObjects();
		playState->readFile("../assets/maps/trivial.txt");
		game->popState();
		});
	addObject(restartButton);
	addEventListener(restartButton);


	//boton menu
	Texture* menuTex = window->getTexture(SDLApplication::VOLVERALMENU);
	Button* goMenu = new Button(this, menuTex, 200, 550);
	goMenu->connect([this]() {
		//volver al menu
		game->popState();
		game->popState();
		//game->pushState(new MainMenuState(game));
		});
	addObject(goMenu);
	addEventListener(goMenu);


	//boton Salir
	Texture* exitTex = window->getTexture(SDLApplication::SALIR);
	Button* exitButton = new Button(this, exitTex, 200, 650);
	exitButton->connect([this]() {
		//salir del juego
		
		});
	addObject(exitButton);
	addEventListener(exitButton);
}


void PauseState::render() const {
	SDL_Renderer* renderer = game->getRenderer();
	SDL_RenderClear(renderer);


	//fondo semitranslucido
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 150);
	SDL_FRect overlay{ 0,0, SDLApplication::WINDOW_WIDTH, SDLApplication::WINDOW_HEIGHT };
	SDL_RenderFillRect(renderer, &overlay);
	GameState::render(); //render botones

	SDL_RenderPresent(renderer);
}

void PauseState::handleEvent(const SDL_Event& e) {
	if (e.type == SDL_EVENT_KEY_DOWN) {
		if (e.key.key == SDLK_ESCAPE) {
			game->popState();
			return;
		}
	}
	GameState::handleEvent(e); //manejo eventos botones
}
