#include "game.h"
#include <string>
#include <SDL3_image/SDL_image.h>
#include <random>
#include "texture.h"
#include "HomedFrog.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// Constantes
constexpr const char* const WINDOW_TITLE = "Frogger 1.0";
constexpr const char* const MAP_FILE = "assets/maps/default.txt";

constexpr const int HOMEFROGNUM = 5;
constexpr const float HOME_FIRST_X = 32;
constexpr const float HOME_Y = 38;
constexpr const float HOME_DISTANCE = 96;
//Las posiciones de las casas, siendo la posición el pixel inferior derecho del cuadrado 2x2 que constituye el centro del sprite de casa.
//Empieza en (32, 38) y se va sumando 96 en la posición horizontal con cada casa consecutiva, según la imagen dada
const Point2D<float> homePositions[HOMEFROGNUM] = { Point2D<float>(HOME_FIRST_X, HOME_Y), 
													Point2D<float>(HOME_FIRST_X + HOME_DISTANCE, HOME_Y), 
													Point2D<float>(HOME_FIRST_X + HOME_DISTANCE * 2, HOME_Y), 
													Point2D<float>(HOME_FIRST_X + HOME_DISTANCE * 3, HOME_Y), 
													Point2D<float>(HOME_FIRST_X + HOME_DISTANCE * 4, HOME_Y) };

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

Game::Game()
	: exit(false), frog(nullptr) //TODO POR NO INICIAR FROG EN NULLPTR 
{
	try {
		// Carga SDL y sus bibliotecas auxiliares
		if (!SDL_Init(SDL_INIT_VIDEO)) {
			throw string("Error inicializando SDL: ") + SDL_GetError() + "\n";
		};

		window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT,0);

		if (!window)
			throw string("window: ") + SDL_GetError() + "\n";

		renderer = SDL_CreateRenderer(window, nullptr);

		if (!renderer)
			throw string("renderer: ") + SDL_GetError() + "\n";

		// Carga las texturas al inicio
		
		for (size_t i = 0; i < textures.size(); i++) {
			auto [name, nrows, ncols] = textureList[i];
			textures[i] = new Texture(renderer, (string(imgBase) + name).c_str(), nrows, ncols);
		}
		
		
		//Variables para leer el archivo
		fstream file(MAP_FILE);
		if (!file) 
			throw string("Error: No se ha encontrado el archivo mapa. El nombre del archivo que se intenta leer es: ") + string(MAP_FILE) + "\n";
		char objType, c_sprType;
		TextureName sprType;
		int pointX, pointY, directionX;

				while (file >> objType) { //Asumo que el archivo tendrá el formato correcto
					if (objType == '#') {
						file.ignore(numeric_limits<streamsize>::max(), '\n');
					}
					else if (objType == 'F') {
						if (!(file >> pointX >> pointY)) {
							throw string("Error: formato invalido para rana en el archivo de mapa: ") + string(MAP_FILE) + "\n";
						};
						frogSpawn = Point2D<float>(pointX, pointY);
						sprType = FROG;
						int health;
						file >> health;
						frog = new Frog{ Vector2D<float>(0, 0), Point2D<float>(pointX, pointY), health, getTexture(sprType), this };

					}
					else if (objType == 'V' || objType == 'L') {

						if (!(file >> pointX >> pointY >> directionX >> c_sprType)) {
							throw string("Error: formato invalido para vehiculo/log en el archivo de mapa: ") + string(MAP_FILE) + "\n";
						}

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
				reachedHomes.push_back(false);
			}

		file.close();
		randomGenerator.seed(time(nullptr));
		srand(SDL_GetTicks());
		waspSpawnTime = getRandomRange(WASP_MIN_SPAWN, WASP_MAX_SPAWN) * 1000;
		currentTime = 0;
	}
	catch(const string& e)
	{
		if (frog) {
			delete frog;		
			frog = nullptr; 
		}

		for (auto& v : vehicles) {
			delete v;
			v = nullptr;
		}
		vehicles.clear(); 
			
		for (auto& l : logs) {
			delete l; 
			l = nullptr; 
		}
		logs.clear();

		for (auto& t : textures) {
				delete t;
				t = nullptr;
		}

		for (auto& h : homedFrogs) {
			delete h;
			h = nullptr;
		}

		homedFrogs.clear();
		reachedHomes.clear();
		if (renderer) SDL_DestroyRenderer(renderer); 
		if (window) SDL_DestroyWindow(window);
		SDL_Quit(); 
		throw; 
	}
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
	for (Wasp* w : wasps) {
		delete w;
		w = nullptr;
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
	for (int i = 0; i < wasps.size(); i++) {
		wasps[i]->Render();
	}
	SDL_RenderPresent(renderer);
}

void
Game::update()
{
	currentTime = SDL_GetTicks();
	for (int i = 0; i < vehicles.size(); i++) {
		vehicles[i]->Update();
	}

	for (int i = 0; i < logs.size(); i++) {
		logs[i]->Update();
	}
	frog->Update();

	if (frog->GetHealth() == 0) {
		cout << "Has perdido" << endl;
		exit = true;
	}

	if (allFrogsHome()) {
		cout << "Has ganado" << endl;
		exit = true;
	}

	for (int i = wasps.size() - 1; i >= 0; i--) { //Se recorre al revés para no saltarse avispas en caso de borrar alguna
		wasps[i]->Update();
		if (!wasps[i]->isAlive()) {
			delete wasps[i];
			wasps[i] = nullptr;
			wasps.erase(wasps.begin() + i);
		}
	}

	if (currentTime >= waspSpawnTime) {
		waspSpawnTime = currentTime + getRandomRange(WASP_MIN_SPAWN, WASP_MAX_SPAWN) * 1000;
		int rndHome;
		do {
			rndHome = getRandomRange(0, HOMEFROGNUM-1);
		} while (reachedHomes[rndHome]);
		wasps.push_back(new Wasp{ homePositions[rndHome] - Point2D<float>(getTexture(WASP)->getFrameWidth() / 2,getTexture(WASP)->getFrameHeight() / 2), Vector2D<float>(0,0), getTexture(WASP), this, (float)(getRandomRange(WASP_MIN_LIFE, WASP_MAX_LIFE) * 1000.0) });
	}
}

void
Game::run()
{
	while (!exit) {
		try {

			update();
			render();
			handleEvents();
			SDL_Delay(FRAME_RATE);
		}
		catch (exception e) {
			cout << e.what() << endl;
		}
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
		} i++;
	} i = 0;

	while (!hasCollisioned && i < vehicles.size()) {
		Collision col = vehicles[i]->CheckCollision(rect);
		if (col.tipo != NONE) {
			collision.tipo = col.tipo;
			hasCollisioned = true;
		} i++;
	} i = 0;

	while (!hasCollisioned && i < wasps.size()) {
		Collision col = wasps[i]->CheckCollision(rect);
		if (col.tipo != NONE) {
			collision.tipo = col.tipo;
			hasCollisioned = true;
		} i++;
	} i = 0;

	while (!hasCollisioned && i < HOMEFROGNUM) {
		Collision col = homedFrogs[i]->CheckCollision(rect);
		if (col.tipo != NONE) {
			collision.tipo = col.tipo;
			hasCollisioned = true;
		} i++;
	}
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
				reachedHomes[i] = true;
				reached = false;
			}
		}
		i++;
	}
	return reached;
}

bool
Game::allFrogsHome() const {
	for (auto& hf : homedFrogs) {
		if (!hf->GetReached())
			return false;
	}
	return true;
}

int Game::getRandomRange(int min, int max) {
	return uniform_int_distribution<int>(min, max)(randomGenerator);
}
