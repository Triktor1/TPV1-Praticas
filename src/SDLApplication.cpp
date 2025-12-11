#include "SDLApplication.h"
#include "GameError.h"
#include "texture.h"
#include <iostream>
#include <string>
#include <SDL3_image/SDL_image.h>
using namespace std;

// Constantes
constexpr const char* const WINDOW_TITLE = "Frogger 3.0";

// Estructura para especificar las texturas que hay que
// cargar y el tamaño de su matriz de frames
struct TextureSpec
{
	const char* name;
	int nrows = 1;
	int ncols = 1;
};


constexpr array<TextureSpec, SDLApplication::NUM_TEXTURES> textureList{
	TextureSpec{"frog.png", 1, 2},
	{"background.png"},
	{"car1.png"},
	{"car2.png"},
	{"car3.png"},
	{"car4.png"},
	{"car5.png"},
	{"log1.png"},
	{"log2.png"},
	{"turtle.png", 1, 7},
	{"wasp.png"},
	{"menuBackground.png"},
	{"texts/CONTINUAR.png"},
	{"texts/ELIGE UN MAPA.png"},
	{"texts/GAME OVER.png"},
	{"texts/HAS GANADO.png"},
	{"texts/left.png"},
	{"texts/right.png"},
	{"texts/Avispado.png"},
	{"texts/Original.png"},
	{"texts/Practica 1.png"},
	{"texts/Trivial.png"},
	{"texts/Veloz.png"},
	{"texts/REINICIAR.png"},
	{"texts/SALIR.png"},
	{"texts/VOLVER AL MENU.png"}
};

constexpr const char* imgBase = "../assets/images/";

SDLApplication::SDLApplication()
	:exit(false)
{
	try {
		// Carga SDL y sus bibliotecas auxiliares
		if (!SDL_Init(SDL_INIT_VIDEO)) {
			throw SDLError();
		};

		window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

		if (!window)
			throw SDLError();

		renderer = SDL_CreateRenderer(window, nullptr);

		if (!renderer)
			throw SDLError();

		// Carga las texturas al inicio
		for (size_t i = 0; i < textures.size(); i++) {
			auto [name, nrows, ncols] = textureList[i];
			textures[i] = new Texture(renderer, (string(imgBase) + name).c_str(), nrows, ncols);
		}
	}
	catch (const GameError& e)
	{
		SDL_Quit();
		throw;
	}
}



SDLApplication::~SDLApplication()
{
	while (!empty()) {
		popState();
	}

	for (Texture* t : textures) {
		delete t;
	}
	SDL_Quit();
}

void
SDLApplication::run()
{
	while (!exit) {
		try {

			update();

			SDL_RenderClear(renderer);
			render();
			SDL_RenderPresent(renderer);

			SDL_Event event;
			while (SDL_PollEvent(&event)) {
			handleEvent(event);
			}

			SDL_Delay(FRAME_RATE);
		}
		catch (exception e) {
			cout << e.what() << endl;
		}
	}
	while(!empty())
		popState();
}

void SDLApplication::mostrarError(const GameError& e) {
	const SDL_MessageBoxButtonData botones[] = {
		{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "Aceptar" }
	};

	const SDL_MessageBoxData datos = {
		SDL_MESSAGEBOX_ERROR,
		nullptr,
		"Error en el juego",
		e.what(),
		SDL_arraysize(botones),
		botones,
		nullptr
	};

	SDL_ShowMessageBox(&datos, nullptr);
}
