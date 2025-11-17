#include "game.h"
#include "Frog.h"
#include "Wasp.h"
#include "HomedFrog.h"
#include "Vehicle.h"
#include "Log.h"
#include "TurtleGroup.h"
#include "GameError.h"

#include <string>
#include <SDL3_image/SDL_image.h>
using namespace std;

// Constantes
constexpr const char* const WINDOW_TITLE = "Frogger 1.0";
constexpr const char* const MAP_FILE = "assets/maps/turtles.txt";

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


//Configuración de botones
const SDL_MessageBoxButtonData resetButtons[] = {
		{ SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 0, "Volver" },
		{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "Reiniciar" },
};

const SDL_MessageBoxColorScheme colorScheme = {
	{ /* .colors (.r, .g, .b) */
		/* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
		{ 255,   200,   0 },
		/* [SDL_MESSAGEBOX_COLOR_TEXT] */
		{   0, 255,   0 },
		/* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
		{ 255, 255,   0 },
		/* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
		{   0,   0, 255 },
		/* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
		{ 255,   0, 255 }
	}
};

const SDL_MessageBoxData resetMessageData = {
		SDL_MESSAGEBOX_BUTTONS_LEFT_TO_RIGHT, /* .flags */
		NULL, /* .window */
		"Reinicio de nivel", /* .title */
		"¿Quieres reiniciar el nivel? Se perderá todo el progreso.", /* .message */
		SDL_arraysize(resetButtons), /* .numbuttons */
		resetButtons, /* .buttons */
		&colorScheme
};

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

		readFile(MAP_FILE);

		buildHomes();

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

	if (frog->getLives() == 0) { 
		cout << "Has perdido" << endl;
		exit = true;
	}

	if (allFrogsHome()) {
		cout << "Has ganado" << endl;
		exit = true;
	}

	if (currentTime >= waspSpawnTime) {
		waspSpawnTime = currentTime + getRandomRange(WASP_MIN_SPAWN, WASP_MAX_SPAWN) * 1000;
		int rndHome;
		do {
			rndHome = getRandomRange(0, HOMEFROGNUM - 1);
		} while (reachedHomes[rndHome]);
		Wasp* wasp = new Wasp{ homePositions[rndHome] - Point2D<float>(getTexture(WASP)->getFrameWidth() / 2,getTexture(WASP)->getFrameHeight() / 2), Vector2D<float>(0,0), getTexture(WASP), this, (float)(getRandomRange(WASP_MIN_LIFE, WASP_MAX_LIFE) * 1000.0) };
		wasp->setAnchor(sceneObjects.insert(sceneObjects.begin(), wasp));
	}

	//Borrado en sceneObjects de los objetos cuyo iterador está en toDelete
	for (Anchor it : toDelete) {
		delete* it;
		sceneObjects.erase(it);
	}
	toDelete.clear();
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
		if (event.type == SDL_EVENT_KEY_DOWN) {
			bool key0 = (event.key.key == SDLK_0);
			if (key0) {
				int buttonID;
				SDL_ShowMessageBox(&resetMessageData, &buttonID);
				if (buttonID == 1) {
				reset();
				}
				return;
			}
		}
	}
}


void
Game::reset() {
	destroySceneObjects();
	readFile(MAP_FILE);
	buildHomes();

}


void
Game::buildHomes() {
	for (int i = 0; i < HOMEFROGNUM; i++) {
		//sceneObjects.push_back(new HomedFrog{ Point2D<float>(homePositions[i] - Point2D<float>(getTexture(FROG)->getFrameWidth() / 2,getTexture(FROG)->getFrameHeight() / 2)), getTexture(FROG), this });
		Point2D<float> homePos(
			homePositions[i].GetX() - getTexture(FROG)->getFrameWidth() / 2.0f,
			homePositions[i].GetY() - getTexture(FROG)->getFrameHeight() / 2.0f
		);
		//declarado asi, para facilidad de luego hacer pushback en scene y en homedfrogs
		HomedFrog* hf = new HomedFrog(homePos, getTexture(FROG), this);
		sceneObjects.push_back(hf);
		homedFrogs.push_back(hf);

		//wasp
		reachedHomes.push_back(false);
	}

}
void
Game::destroySceneObjects() {
	frog = nullptr; 

	for (SceneObject* so : sceneObjects) {
		delete so; 
	}
	sceneObjects.clear();
	homedFrogs.clear();
	reachedHomes.clear();
	toDelete.clear();


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
	for (int i = 0; i < HOMEFROGNUM; i++) {
		if (homedFrogs[i]->GetReached())
			count++;
	}
	return count == HOMEFROGNUM;
}

int Game::getRandomRange(int min, int max) {
	return uniform_int_distribution<int>(min, max)(randomGenerator);
}

void Game::readFile(const char* fileRoute) {

	//Lectura de archivo
	fstream file(fileRoute);
	if (!file)
		throw string("Error: No se ha encontrado el archivo mapa. El nombre del archivo que se intenta leer es: ") + string(MAP_FILE) + "\n";
	char objType;

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
			sceneObjects.push_back(new TurtleGroup(this, file));
			break;
		}
	}
	file.close();
}

void Game::deleteAfter(Anchor it) {
	toDelete.push_back(it);
}

void Game::mostrarError(const GameError& e) {
	const SDL_MessageBoxButtonData botones[] = {
		{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "Aceptar" }
	};

	const SDL_MessageBoxData datos = {
		SDL_MESSAGEBOX_ERROR,
		nullptr,                // ventana asociada
		"Error en el juego",    // título genérico
		e.what(),               // mensaje con el texto de la excepción
		SDL_arraysize(botones),
		botones,
		nullptr
	};

	SDL_ShowMessageBox(&datos, nullptr);
}
