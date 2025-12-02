#include "PauseState.h"
#include "PlayState.h"
#include "Button.h"
#include "MainMenuState.h"
#include "SDLApplication.h"
#include <SDL3/SDL.h>

PauseState::PauseState(SDLApplication* window, PlayState* previousState, bool paused) :
	GameState(window), playState(previousState)
{

	//boton continuar
	Texture* continueTex = window->getTexture(SDLApplication::CONTINUAR);
	Button* continueButton = new Button(this, continueTex, game->WINDOW_WIDTH/2-game->getTexture(game->CONTINUAR)->getFrameWidth()/2, 150);
	continueButton->connect([this]() {
		//continuar
		game->popState();
		});
	addObject(continueButton);
	addEventListener(continueButton);
	buttons.push_back(continueButton);


	//boton Reiniciar
	Texture* restartTex = window->getTexture(SDLApplication::REINICIAR);
	Button* restartButton = new Button(this, restartTex, game->WINDOW_WIDTH / 2 - game->getTexture(game->REINICIAR)->getFrameWidth() / 2, 250);
	restartButton->connect([this]() {
		//reinicio
		playState->destroySceneObjects();
		std::string mapFile = playState->getFile();
		game->popState();
		game->popState();
		game->pushState(std::make_shared<PlayState>(game, mapFile));
		return;
		});
	addObject(restartButton);
	addEventListener(restartButton);
	buttons.push_back(restartButton);


	//boton menu
	Texture* menuTex = window->getTexture(SDLApplication::VOLVERALMENU);
	Button* goMenu = new Button(this, menuTex, game->WINDOW_WIDTH / 2 - game->getTexture(game->VOLVERALMENU)->getFrameWidth() / 2, 350);
	goMenu->connect([this]() {
		//volver al menu
		game->popState();
		game->popState();
		//game->pushState(new MainMenuState(game, game->getTexture(game->BACKGROUND), game->getTexture(game->ELIGEUNMAPA)));
		});
	addObject(goMenu);
	addEventListener(goMenu);
	buttons.push_back(goMenu);
}

PauseState::~PauseState() {
	for(Button* b : buttons) {
		delete b;
	}
}


void PauseState::render() const {
	SDL_Renderer* renderer = game->getRenderer();
	SDL_RenderClear(renderer);

	//No hemos conseguido hacer un fondo translúcido
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
