#include "EndState.h"
#include "Button.h"
#include "playState.h"
#include "MainMenuState.h"
#include "SDLApplication.h"
#include <SDL3/SDL.h>

EndState::EndState(SDLApplication* window, PlayState* previousState, bool victory) :
	GameState(window), playState(previousState), victory(victory)
{
	//obtencion de la textura del resultado segun bool victory
	resultTexture = window->getTexture(victory ? SDLApplication::HASGANADO : SDLApplication::GAMEOVER);

	
	//boton menu
	Texture* menubutton = window->getTexture(SDLApplication::VOLVERALMENU);
	Button* goMenu = new Button(this, menubutton, 200, 350);
	goMenu->connect([this]() {
			//volver al menu
		});
	addObject(goMenu);
	addEventListener(goMenu);

	//boton salir
	Texture* exitbutton = window->getTexture(SDLApplication::SALIR);
	Button* exitGame = new Button(this, exitbutton, 200, 450);
	exitGame->connect([this]() {
			//salir del juego
		});
	addObject(exitGame);
	addEventListener(exitGame);
}

void EndState::render() const 
{
	SDL_Renderer* renderer = game->getRenderer();
	//fondo negro
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	//Mostrar si ganas o pierdes
	if (resultTexture) {
		SDL_FRect cuerpo{ 200,100,400,150 };
		resultTexture->render(cuerpo);
	}

	GameState::render(); //encargado del render de los botoness
}

void EndState::handleEvent(const SDL_Event& e) 
{
	GameState::handleEvent(e); 
}
