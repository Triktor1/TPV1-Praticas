#include "PlayState.h"
#include "SDLApplication.h"
#include "Frog.h"
#include "Wasp.h"
#include "HomedFrog.h"
#include "Vehicle.h"
#include "Log.h"
#include "TurtleGroup.h"
#include "GameError.h"

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

const SDL_MessageBoxData resetMessageData = {
		SDL_MESSAGEBOX_BUTTONS_LEFT_TO_RIGHT, /* .flags */
		NULL, /* .window */
		"Reinicio de nivel", /* .title */
		"¿Quieres reiniciar el nivel? Se perderá todo el progreso.", /* .message */
		SDL_arraysize(resetButtons), /* .numbuttons */
		resetButtons /* .buttons */
};

PlayState::PlayState(SDLApplication* game) :
	GameState(game), frog(nullptr), exit(false)
{
	buildHomes();

	randomGenerator.seed(time(nullptr));
	srand(SDL_GetTicks());
	waspSpawnTime = getRandomRange(WASP_MIN_SPAWN, WASP_MAX_SPAWN) * 1000;
	currentTime = 0;
}

void PlayState::render() const {
	SDL_Renderer* renderer = game->getRenderer();
	SDL_RenderClear(renderer);
	game->getTexture(game->BACKGROUND)->render();

	for (SceneObject* so : sceneObjects) {
		so->Render();
	}
	SDL_RenderPresent(renderer);
}

void PlayState::update() {
	currentTime = SDL_GetTicks();
	for (SceneObject* so : sceneObjects) {
		so->Update();
	}

	if (frog->getLives() == 0) {
		std::cout << "Has perdido" << std::endl;
		exit = true;
	}

	if (allFrogsHome()) {
		std::cout << "Has ganado" << std::endl;
		exit = true;
	}

	if (currentTime >= waspSpawnTime) {
		waspSpawnTime = currentTime + getRandomRange(WASP_MIN_SPAWN, WASP_MAX_SPAWN) * 1000;
		int rndHome;
		do {
			rndHome = getRandomRange(0, HOMEFROGNUM - 1);
		} while (reachedHomes[rndHome]);
		Wasp* wasp = new Wasp{ homePositions[rndHome] - Point2D<float>(getGame()->getTexture(getGame()->WASP)->getFrameWidth() / 2, getGame()->getTexture(getGame()->WASP)->getFrameHeight() / 2), Vector2D<float>(0,0), getGame()->getTexture(getGame()->WASP), this, (float)(getRandomRange(WASP_MIN_LIFE, WASP_MAX_LIFE) * 1000.0) };
		auto aPS = wasp->getAnchorPS();
		wasp->setAnchorPS(sceneObjects.insert(sceneObjects.end(), wasp));
		auto aGS = addObject(wasp);
		wasp->setAnchorGS(aGS);
	}

	//Borrado en sceneObjects de los objetos cuyo iterador está en toDelete
	for (Anchor it : toDelete) {
		delete* it;
		sceneObjects.erase(it);
	}
	toDelete.clear();
}

void PlayState::handleEvents() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_EVENT_QUIT)
			exit = true;

		frog->handleEvent(event);
		if (event.type == SDL_EVENT_KEY_DOWN) {
			bool key0 = (event.key.key == SDLK_0);
			if (key0) {
				int buttonID;
				SDL_ShowMessageBox(&resetMessageData, &buttonID);
				if (buttonID == 1) {
					getGame()->replaceState(new PlayState(getGame()));
				}
				return;
			}
		}
	}
}

Collision
PlayState::checkCollision(const SDL_FRect& rect) const
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

Point2D<float> PlayState::getFrogSpawn() const {
	return frogSpawn;
}

void PlayState::setFrogSpawn(float x, float y) {
	frogSpawn = Point2D<float>(x, y);
}

bool PlayState::tryReachHome(const SDL_FRect& hitbox) {
	bool reached = true;
	int i = 0;
	while (reached && i < homedFrogs.size()) {
		SDL_FRect homeRect = {
			homePositions[i].GetX() - getGame()->getTexture(getGame()->FROG)->getFrameWidth() / 2.0f,
			homePositions[i].GetY() - getGame()->getTexture(getGame()->FROG)->getFrameHeight() / 2.0f,
			(float)getGame()->getTexture(getGame()->FROG)->getFrameWidth(),
			(float)getGame()->getTexture(getGame()->FROG)->getFrameHeight()
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
PlayState::allFrogsHome() const {
	int count = 0;
	for (int i = 0; i < HOMEFROGNUM; i++) {
		if (homedFrogs[i]->GetReached())
			count++;
	}
	return count == HOMEFROGNUM;
}

void PlayState::destroySceneObjects() {
	frog = nullptr;

	for (SceneObject* so : sceneObjects) {
		delete so;
	}
	sceneObjects.clear();
	homedFrogs.clear();
	reachedHomes.clear();
	toDelete.clear();


}

int PlayState::getRandomRange(int min, int max) {
	return std::uniform_int_distribution<int>(min, max)(randomGenerator);
}

//Metodo que agrupa TODO a borrar para la excepcion
void PlayState::destroyAllElements() {

	frog = nullptr;
	for (SceneObject* so : sceneObjects) {
		delete so;
		so = nullptr;
	}
	sceneObjects.clear();

	reachedHomes.clear();

	for (auto& t : game->textures) {
		delete t;
		t = nullptr;
	}
}


void PlayState::deleteAfter(Anchor it) {
	toDelete.push_back(it);
}

void
PlayState::buildHomes() {
	for (int i = 0; i < HOMEFROGNUM; i++) {
		//sceneObjects.push_back(new HomedFrog{ Point2D<float>(homePositions[i] - Point2D<float>(getTexture(FROG)->getFrameWidth() / 2,getTexture(FROG)->getFrameHeight() / 2)), getTexture(FROG), this });
		Point2D<float> homePos(
			homePositions[i].GetX() - game->getTexture(game->FROG)->getFrameWidth() / 2.0f,
			homePositions[i].GetY() - game->getTexture(game->FROG)->getFrameHeight() / 2.0f
		);
		//declarado asi, para facilidad de luego hacer pushback en scene y en homedfrogs
		HomedFrog* hf = new HomedFrog(homePos, game->getTexture(game->FROG), this);
		sceneObjects.push_back(hf);
		homedFrogs.push_back(hf);

		//wasp
		reachedHomes.push_back(false);
	}

}

PlayState::Anchor PlayState::addSceneObject(SceneObject* object) {
	sceneObjects.push_back(object);
	return --sceneObjects.end();
}

void PlayState::removeSceneObject(Anchor it) {
	sceneObjects.erase(it);
}

void PlayState::readFile(const char* fileRoute) {
	//Lectura de archivo
	std::fstream file(fileRoute);
	if (!file)
		throw FileNotFoundError(fileRoute);
	char objType;
	int line = 0;
	while (file >> objType) { //Asumo que el archivo tendrá el formato correcto
		line++;
		try
		{
			switch (objType) {
			case '#':
				file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
			case 'W': {
				Wasp* wasp = new Wasp(this, file);
				wasp->setAnchorGS(addObject(wasp));
				wasp->setAnchorPS(sceneObjects.insert(sceneObjects.end(), wasp));
				break;
			}
			default:
				throw FileFormatError(fileRoute, line, "Tipo de objeto desconocido");
			}
		}
		catch (const GameError& e) {
			throw FileFormatError(fileRoute, line, e.what());
		}
	}
	file.close();
}
