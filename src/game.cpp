#include "game.h"

#include <string>

#include <SDL3_image/SDL_image.h>

#include "texture.h"

#include <iostream>
#include <fstream>
using namespace std;

// Constantes
constexpr const char* const WINDOW_TITLE = "Frogger 1.0";
constexpr const char* const MAP_FILE = "assets/maps/default.txt";

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

	//Variables para leer el archivo
	fstream file(MAP_FILE);
	char objType, c_sprType;
	TextureName sprType;
	int pointX, pointY, directionX;
	bool validType;
	if (!file) {
		cout << "No se ha encontrado el archivo." << endl;
	}
	else {
		while (file >> objType) { //Asumo que el archivo tendrá el formato correcto
			if (objType == 'V' || objType == 'L' || objType == 'F') {

				file >> pointX;
				file >> pointY;
				file >> directionX;
				file >> c_sprType;

				switch (objType) {
				case 'V':
					switch (c_sprType) {
					case '1': sprType = CAR1; break;
					case '2': sprType = CAR2; break;
					case '3': sprType = CAR3; break;
					case '4': sprType = CAR4; break;
					case '5': sprType = CAR5; break;
					default:  sprType = CAR1; break;
					}
					vehicles.push_back(new Vehicle{ Vector2D<int>(directionX, 0), Point2D<int>(pointX, pointY), getTexture(sprType), this });
					break;
				case 'L':
					switch (c_sprType) {
					case '0': sprType = LOG1; break;
					case '1': sprType = LOG2; break;
					}
					//logs.push_back(new Log{to el tinglao});
					break;
				case 'F':
					break;
				default:
					break;
				}
			}
			else {
				string a;
				std::getline(file, a);
			}
		}
	}
	file.close();

	// Configura que se pueden utilizar capas translúcidas
	// SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

Game::~Game()
{
	for (Texture* t : textures) {
		delete t;
		t = nullptr;
	}
	for (Vehicle* e : vehicles) {
		delete e;
		e = nullptr;
	}
	// TODO: liberar memoria reservada por la clase
}

void
Game::render() const
{
	SDL_RenderClear(renderer);

	// TODO
	getTexture(BACKGROUND)->render();
	for (int i = 0; i < vehicles.size(); i++) {
		vehicles[i]->Render();
	}


	SDL_RenderPresent(renderer);
}

void
Game::update()
{
	for (int i = 0; i < vehicles.size(); i++) {
		vehicles[i]->Update();
	}
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
