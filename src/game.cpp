#include "game.h"

#include <string>

#include <SDL3_image/SDL_image.h>

#include "texture.h"
//#include "../Vehicle.h"

using namespace std;

// Constantes
constexpr const char* const WINDOW_TITLE = "Frogger 1.0";
constexpr const char* const MAP_FILE = "../assets/maps/default.txt";

// Estructura para especificar las texturas que hay que
// cargar y el tamaño de su matriz de frames
struct TextureSpec
{
	const char* name;
	int nrows = 1;
	int ncols = 1;
};

constexpr const char* imgBase = "assets/images/";

constexpr array<TextureSpec, Game::NUM_TEXTURES> textureList{
	TextureSpec{"frog.png", 1, 2},
	{"background.png"},
	{"car1.png"},
	{"car2.png"},
	{"car3.png"},
	{"car4.png"},
	{"car5.png"},
	{"goal.png"},
	{"log1.png"},
	{"log2.png"},
	{"turtle.png", 1, 7},
	{"wasp.png"},
};

Game::Game()
  : exit(false)
{
	// Carga SDL y sus bibliotecas auxiliares
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow(WINDOW_TITLE,
	                          WINDOW_WIDTH,
	                          WINDOW_HEIGHT,
	                          0);

	if (window == nullptr)
		throw "window: "s + SDL_GetError();

	renderer = SDL_CreateRenderer(window, nullptr);

	if (renderer == nullptr)
		throw "renderer: "s + SDL_GetError();

	// Carga las texturas al inicio
	for (size_t i = 0; i < textures.size(); i++) {
		auto [name, nrows, ncols] = textureList[i];
		textures[i] = new Texture(renderer, (string(imgBase) + name).c_str(), nrows, ncols);
	}

	car1 = new Vehicle( Vector2D<int>{-48, 0}, Point2D<int>{50, 372},  getTexture(CAR1), this);
	car2 = new Vehicle{ Vector2D<int>{-48, 0}, Point2D<int>{200, 372},  getTexture(CAR1), this};
	car3 = new Vehicle{ Vector2D<int>{-48, 0}, Point2D<int>{350, 372},  getTexture(CAR1), this};

	// Configura que se pueden utilizar capas translúcidas
	// SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

Game::~Game()
{
	for (size_t i = 0; i < textures.size(); i++) {
		delete Game::textures[i];
	}
	delete car1;
	delete car2;
	delete car3;
	// TODO: liberar memoria reservada por la clase
}

void
Game::render() const
{
	SDL_RenderClear(renderer);

	// TODO
	getTexture(BACKGROUND)->render();
	car1->Render();
	car2->Render();
	car3->Render();
	
	
	SDL_RenderPresent(renderer);
}

void
Game::update()
{
	car1->Update();
	car2->Update();
	car3->Update();
	// TODO
}

void
Game::run()
{
	while (!exit) {
		update();
		//checkCollision();
		render();
		handleEvents();
		SDL_Delay(FRAME_RATE);
	}
}

void
Game::handleEvents()
{
	SDL_Event event;

	// Only quit is handled directly, everything else is delegated
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_EVENT_QUIT)
			exit = true;

		// TODO
	}
}

bool
Game::checkCollision(const SDL_FRect& rect) const
{
	// TODO:
	return false;
}

/*

#include "game.h"

int main(int argc, char* argv[])
{
	Game().run();

	// TODO: manejar excepciones

	return 0;
}

*/
