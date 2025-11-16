#include "game.h"
#include <string>
#include <vector>
#include <SDL3_image/SDL_image.h>
#include <random>
#include "texture.h"
#include "HomedFrog.h"
#include <iostream>
#include <fstream>
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
	: exit(false), frog(nullptr)
{
	try {
		// Carga SDL y sus bibliotecas auxiliares
		if (!SDL_Init(SDL_INIT_VIDEO)) {
			throw string("Error inicializando SDL: ") + SDL_GetError() + "\n";
		};

		window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

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
			switch (objType) {
			case '#':
				file.ignore(numeric_limits<streamsize>::max(), '\n');
				break;
			case 'F':
				frog = new Frog(this, file);
				sceneObjects.push_back(frog);
				break;
			case 'L':
				sceneObjects.push_back(new Log(this, file));
				break;
			case 'V':
				sceneObjects.push_back(new Vehicle(this, file));
				break;
			case 'T':

				break;
			}
			
			
			
			/*if (objType == '#') {
				file.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			else if (objType == 'F') {
				sceneObjects.push_back(Frog::readFile(file, this));
			}
			else if (objType == 'V' || objType == 'L') {

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
			}*/

		}
		
	for (int i = 0; i < 5; i++) {
		//sceneObjects.push_back(new HomedFrog{ Point2D<float>(homePositions[i] - Point2D<float>(getTexture(FROG)->getFrameWidth() / 2,getTexture(FROG)->getFrameHeight() / 2)), getTexture(FROG), this });
		reachedHomes.push_back(false);
	}

	file.close();
	randomGenerator.seed(time(nullptr));
	srand(SDL_GetTicks());
	waspSpawnTime = getRandomRange(WASP_MIN_SPAWN, WASP_MAX_SPAWN) * 1000;
	currentTime = 0;
}
catch (const string& e)
{
	destroyAllElements();
	SDL_Quit();
	throw e;
}
}

Game::~Game()
{
	destroyAllElements();
	SDL_Quit();
}

void
Game::render() const
{
	SDL_RenderClear(renderer);

	getTexture(BACKGROUND)->render();

	for (SceneObject* so : sceneObjects) {
		so->Render();
	}

	SDL_RenderPresent(renderer);
}

void
Game::update()
{
	currentTime = SDL_GetTicks();
	for (SceneObject* so : sceneObjects) {
		so->Update();
	}

	//if (frog->GetHealth() == 0) { //no se como hacer esto bien ayuda
	//	cout << "Has perdido" << endl;
	//	exit = true;
	//}

	if (allFrogsHome()) {
		cout << "Has ganado" << endl;
		exit = true;
	}

	//for (int i = wasps.size() - 1; i >= 0; i--) { //Se recorre al revés para no saltarse avispas en caso de borrar alguna
	//	wasps[i]->Update();
	//	if (!wasps[i]->isAlive()) {
	//		delete wasps[i];
	//		wasps[i] = nullptr;
	//		wasps.erase(wasps.begin() + i);
	//	}
	//}

	if (currentTime >= waspSpawnTime) {
		waspSpawnTime = currentTime + getRandomRange(WASP_MIN_SPAWN, WASP_MAX_SPAWN) * 1000;
		int rndHome;
		do {
			rndHome = getRandomRange(0, HOMEFROGNUM - 1);
		} while (reachedHomes[rndHome]);
		//wasps.push_back(new Wasp{ homePositions[rndHome] - Point2D<float>(getTexture(WASP)->getFrameWidth() / 2,getTexture(WASP)->getFrameHeight() / 2), Vector2D<float>(0,0), getTexture(WASP), this, (float)(getRandomRange(WASP_MIN_LIFE, WASP_MAX_LIFE) * 1000.0) });
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

//Metodo que agrupa TODO a borrar para la excepcion
void
Game::destroyAllElements() {

	frog = nullptr;
	for (SceneObject* so : sceneObjects) {
		delete so;
		so = nullptr;
	}
	sceneObjects.clear();

	reachedHomes.clear();

	for (auto& t : textures) {
		delete t;
		t = nullptr;
	}

	if (renderer) SDL_DestroyRenderer(renderer);
	if (window) SDL_DestroyWindow(window);
}

Collision
Game::checkCollision(const SDL_FRect& rect) const
{
	Collision collision;
	collision.tipo = NONE; //Inicializamos en tipo NONE (sin colisión)

	for (SceneObject* so : sceneObjects) {
		Collision col = so->checkCollision(rect);
		if (col.tipo != NONE) {
			collision.tipo = col.tipo;
			collision.speed = col.speed;
			return collision;
		}
	}
	return collision;
}

Point2D<float> Game::getFrogSpawn() const {
	return frogSpawn;
}

void Game::setFrogSpawn(float x, float y) {
	frogSpawn = Point2D<float>(x, y);
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
	int count = 0;
	//for (int i = 0; i < HOMEFROGNUM; i++) {
	//	if (homedFrogs[i]->GetReached())
	//		count++;
	//}
	return count == HOMEFROGNUM;
}

int Game::getRandomRange(int min, int max) {
	return uniform_int_distribution<int>(min, max)(randomGenerator);
}
