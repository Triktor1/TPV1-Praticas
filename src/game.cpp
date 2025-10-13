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
	car4 = new Vehicle{ Vector2D<int>{48, 0}, Point2D<int>{25, 342},  getTexture(CAR2), this};
	car5 = new Vehicle{ Vector2D<int>{48, 0}, Point2D<int>{175, 342},  getTexture(CAR2), this};
	car6 = new Vehicle{ Vector2D<int>{48, 0}, Point2D<int>{325, 342},  getTexture(CAR2), this};
	car7 = new Vehicle{ Vector2D<int>{-72, 0}, Point2D<int>{175, 312},  getTexture(CAR3), this};
	car8 = new Vehicle{ Vector2D<int>{-72, 0}, Point2D<int>{325, 312},  getTexture(CAR3), this};
	car9 = new Vehicle{ Vector2D<int>{-72, 0}, Point2D<int>{475, 312},  getTexture(CAR3), this};
	car10 = new Vehicle{ Vector2D<int>{48, 0}, Point2D<int>{150, 280},  getTexture(CAR4), this};
	car11 = new Vehicle{ Vector2D<int>{48, 0}, Point2D<int>{0, 280},  getTexture(CAR4), this};
	car12 = new Vehicle{ Vector2D<int>{48, 0}, Point2D<int>{-150, 280},  getTexture(CAR4), this};
	car13 = new Vehicle{ Vector2D<int>{-72, 0}, Point2D<int>{165, 252},  getTexture(CAR5), this};
	car14 = new Vehicle{ Vector2D<int>{-72, 0}, Point2D<int>{365, 252},  getTexture(CAR5), this};
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
	delete car4;
	delete car5;
	delete car6;
	delete car7;
	delete car8;
	delete car9;
	delete car10;
	delete car11;
	delete car12;
	delete car13;
	delete car14;
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
	car4->Render();
	car5->Render();
	car6->Render();
	car7->Render();
	car8->Render();
	car9->Render();
	car10->Render();
	car11->Render();
	car12->Render();
	car13->Render();
	car14->Render();
	
	
	SDL_RenderPresent(renderer);
}

void
Game::update()
{
	car1->Update();
	car2->Update();
	car3->Update();
	car4->Update();
	car5->Update();
	car6->Update();
	car7->Update();
	car8->Update();
	car9->Update();
	car10->Update();
	car11->Update();
	car12->Update();
	car13->Update();
	car14->Update();
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
