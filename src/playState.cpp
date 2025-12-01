#include "PlayState.h"
#include "Frog.h"
#include "Wasp.h"
#include "HomedFrog.h"
#include "Vehicle.h"
#include "Log.h"
#include "TurtleGroup.h"


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

void PlayState::handleEvents() {

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
PlayState::allFrogsHome() const {
	int count = 0;
	for (int i = 0; i < HOMEFROGNUM; i++) {
		if (homedFrogs[i]->GetReached())
			count++;
	}
	return count == HOMEFROGNUM;
}

int PlayState::getRandomRange(int min, int max) {
	return uniform_int_distribution<int>(min, max)(randomGenerator);
}

void PlayState::deleteAfter(Anchor it) {
	toDelete.push_back(it);
}
