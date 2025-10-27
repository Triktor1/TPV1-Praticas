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

void firstTest()
{
	
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	if (!SDL_Init(SDL_INIT_VIDEO)) { // activa SDL (añadir SDL_INIT_AUDIO, etc. si procede)
		throw string("Error al inicializar SDL: ") + SDL_GetError();
		
	} 

	// Crea la ventana y el renderizador
	if (!SDL_CreateWindowAndRenderer("Frogger",
		WIN_WIDTH, WIN_HEIGHT, 0,
		&window, &renderer));
	throw string("Error cargando SDL: ") + SDL_GetError(); 
	// Rellena la pantalla de negro
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
		// Espera 5 segundos
		SDL_Delay(5000);

	// Libera los recursos y desactiva SDL
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main(int argc, char* argv[])
{
	try {
		firstTest(); 
	}
	catch (const string& e) {
		cout << "Error fatal en la inicialización del programa: " << e << endl; 
		return EXIT_FAILURE;
	}

	try {
		Game().run();
	}
	catch (const string& e) {
		cout << "Error fatal en la aplicación" << e << endl; 
		return EXIT_FAILURE;
	}
	return 0;
}
