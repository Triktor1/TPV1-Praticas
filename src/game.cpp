#include "game.h"

#include <string>

#include <SDL3_image/SDL_image.h>

#include "texture.h"

#include "HomedFrog.h"

#include <iostream>
#include <fstream>
using namespace std;

// Constantes
constexpr const char* const WINDOW_TITLE = "Frogger 1.0";
constexpr const char* const MAP_FILE = "assets/maps/default.txt";

constexpr int HOMEFROGNUM = 5;
//Las posiciones de las casas, siendo la posición el pixel inferior derecho del cuadrado 2x2 que constituye el centro del sprite de casa.
//Empieza en (32, 38) y se va sumando 96 en la posición horizontal con cada casa consecutiva, según la imagen dada
const Point2D<float> homePositions[HOMEFROGNUM] = { Point2D<float>(32,38), Point2D<float>(128, 38), Point2D<float>(224, 38), Point2D<float>(320, 38), Point2D<float>(416, 38) };

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
	{"log1.png"},
	{"log2.png"},
	{"turtle.png", 1, 7},
	{"wasp.png"},
};

Point2D<float> frogSpawn;

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
	if (!file) {
		cout << "No se ha encontrado el archivo." << endl;
	}
	else {
		while (file >> objType) { //Asumo que el archivo tendrá el formato correcto

			if (objType == '#') {
				file.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			else if (objType == 'F') {
				file >> pointX;
				file >> pointY;
				frogSpawn = Point2D<float>(pointX, pointY);
				sprType = FROG;
				frog = new Frog{ Vector2D<float>(0, 0), Point2D<float>(pointX, pointY), 3, getTexture(sprType), this };

			}
			else if (objType == 'V' || objType == 'L') {

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
					vehicles.push_back(new Vehicle{ Vector2D<float>(directionX, 0), Point2D<float>(pointX, pointY), getTexture(sprType), this });
					break;
				case 'L':
					switch (c_sprType) {
					case '0': sprType = LOG1; break;
					case '1': sprType = LOG2; break;
					default:  sprType = LOG1; break;
					}
					logs.push_back(new Log{ Vector2D<float>(directionX, 0), Point2D<float>(pointX, pointY), getTexture(sprType), this });
					break;
				default:
					break;
				}
			}

		}
	for (int i = 0; i < 5; i++) {
		homedFrogs.push_back(new HomedFrog{ Point2D<float>(homePositions[i] - Point2D<float>(getTexture(FROG)->getFrameWidth() / 2,getTexture(FROG)->getFrameHeight() / 2)), getTexture(FROG), this });
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
	for (Log* e : logs) {
		delete e;
		e = nullptr;
	}
	delete frog;
	for (HomedFrog* hf : homedFrogs) {
		delete hf;
		hf = nullptr;
	}
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
	for (int i = 0; i < logs.size(); i++) {
		logs[i]->Render();
	}
	frog->Frog::Render();
	for (int i = 0; i < homedFrogs.size(); i++) {
		homedFrogs[i]->Render();
	}
	SDL_RenderPresent(renderer);
}

void
Game::update()
{
	for (int i = 0; i < vehicles.size(); i++) {
		vehicles[i]->Update();
	}
	for (int i = 0; i < logs.size(); i++) {
		logs[i]->Update();
	}
	frog->Update();

	if (frog->GetHealth() == 0 ) {
		cout << "Has perdido" << endl; 
		exit = true;
	}

	if (allFrogsHome()) {
		cout << "Has ganado" << endl;
		exit = true;
		
	}
}

void
Game::run()
{
	while (!exit) {
		update();
		render();
		handleEvents();
		SDL_Delay(FRAME_RATE);
	}
}

void
Game::handleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_EVENT_QUIT)
			exit = true;

		frog->HandleEvent(event);
	}
}

Collision
Game::checkCollision(const SDL_FRect& rect) const
{
	Collision collision;
	collision.tipo = NONE; //Inicializamos en tipo NONE (sin colisión)

	bool hasCollisioned = false;
	int i = 0;
	while (!hasCollisioned && i < logs.size()) {
		Collision col = logs[i]->CheckCollision(rect);
		if (col.tipo != NONE) {
			collision.tipo = col.tipo;
			collision.speed = col.speed;
			hasCollisioned = true;
		}
		i++;
	}
	i = 0;

	while (!hasCollisioned && i < vehicles.size()) {
		Collision col = vehicles[i]->CheckCollision(rect);
		if (col.tipo != NONE) {
			collision.tipo = col.tipo;
			hasCollisioned = true;
		}
		i++;
	}
	i = 0;

	while (!hasCollisioned && i < HOMEFROGNUM) {
		Collision col = homedFrogs[i]->CheckCollision(rect);
		if (col.tipo != NONE) {
			collision.tipo = col.tipo;
			hasCollisioned = true;
		}
		i++;
	}
	i = 0;

	return collision;
}

Point2D<float> Game::getFrogSpawn() const {
	return frogSpawn;
}


bool Game::tryReachHome(const SDL_FRect& hitbox) {
	bool reached = true;
	int i = 0;
	while (reached && i < homedFrogs.size()) {
		SDL_FRect homeRect = {
			homePositions[i].GetX() - getTexture(FROG)->getFrameWidth() / 2.0f,
			homePositions[i].GetY() - getTexture(FROG)->getFrameHeight() / 2.0f,
			(float)getTexture(FROG)->getFrameWidth(),
			(float)getTexture(FROG)->getFrameHeight()
		};

		if (SDL_HasRectIntersectionFloat(&hitbox, &homeRect)) {
			if (!homedFrogs[i]->GetReached()) {
				homedFrogs[i]->SetReached(true);
				reached = false;
			}
		}
		i++;
	}
	return reached;
}

bool 
Game::allFrogsHome() const {
	for (auto &hf : homedFrogs) {
		if (!hf->GetReached())
			return false;
	}
	return true;
}
