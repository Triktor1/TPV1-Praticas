//Víctor Castro Álvarez
//Óscar Silva Urbina

#include <iostream>
#include "playState.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "Vector2D.h"
#include "SDLApplication.h"
#include <string>
#include "GameError.h"

using namespace std;

using uint = unsigned int; // alias para el tipo unsigned int

// Dimensiones de la ventana
constexpr uint WIN_WIDTH = 800;
constexpr uint WIN_HEIGHT = 600;

int main(int argc, char* argv[])
{
	try {
		SDLApplication game;
		game.pushState(new PlayState(&game));

		game.run();
		
	}
	catch (const GameError e) {
		SDLApplication::mostrarError(e);
		return 1;
	}
	return 0;
}
