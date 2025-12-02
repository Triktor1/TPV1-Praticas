#include "EndState.h"
#include "Button.h"
#include "MainMenuState.h"
#include "SDLApplication.h"

EndState::EndState(SDLApplication* window, bool victory) :
	GameState(window), victory(victory)
{
	//obtencion de la textura del resultado segun bool victory
	resultTexture = window->getTexture(victory ? SDLApplication::HASGANADO : SDLApplication::GAMEOVER);

	//boton menu
	Texture* menuTex = window->getTexture(SDLApplication::VOLVERALMENU);
	Button* goMenu = new Button(this, menuTex, game->WINDOW_WIDTH/2-game->getTexture(game->VOLVERALMENU)->getFrameWidth()/2, 200);
	goMenu->connect([this]() {
		game->popState();
		});
	addObject(goMenu);
	addEventListener(goMenu);

	//boton salir
	Texture* exitTex = window->getTexture(SDLApplication::SALIR);
	Button* exitGame = new Button(this, exitTex, game->WINDOW_WIDTH / 2 - game->getTexture(game->SALIR)->getFrameWidth() / 2, 300);
	exitGame->connect([this]() {
		game->setExit(true);
		});
	addObject(exitGame);
	addEventListener(exitGame);
}

void EndState::render() const 
{
	SDL_Renderer* renderer = game->getRenderer();
	SDL_RenderClear(renderer);
	//fondo negro
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	//Mostrar si ganas o pierdes
	if (resultTexture) {
		SDL_FRect cuerpo{ 100,100,250,30 };
		resultTexture->render(cuerpo);
	}

	GameState::render(); //encargado del render de los botoness
	SDL_RenderPresent(renderer);
}

void EndState::handleEvent(const SDL_Event& e) 
{
	GameState::handleEvent(e); 
}
