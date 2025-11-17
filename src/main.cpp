//Víctor Castro Álvarez
//Óscar Silva Urbina

#include <iostream>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "Vector2D.h"
#include "game.h"
#include "Vehicle.h"
#include <string>

using namespace std;

using uint = unsigned int; // alias para el tipo unsigned int

// Dimensiones de la ventana
constexpr uint WIN_WIDTH = 800;
constexpr uint WIN_HEIGHT = 600;

int main(int argc, char* argv[])
{
	try {
		Game game;
		game.run();
	}
	catch (const string& e) {
		cout << "Error fatal en la aplicacion: \n" << e << endl; 
	}
	return 0;
}
