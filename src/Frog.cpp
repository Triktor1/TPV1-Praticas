#include "Frog.h"
#include "GameError.h"
#include "playState.h"
#include "SDLApplication.h"
#include <conio.h>

Frog::Frog(Vector2D<float> lastDir, Point2D<float> position, int health, Texture* texture, PlayState* game) :
	SceneObject(position, texture, game),
	lastDir(lastDir),
	health(health),
	anim(0),
	angle(0.0)
{
	this->game = game;
}

Frog::Frog(PlayState* game, std::istream& file) :
	SceneObject(game, file),
	anim(0),
	angle(0.0)
{
	this->game = game;
	float pointX, pointY;
	int health;
	if (!(file >> pointX >> pointY >> health)) {	
		throw GameError("Tipo incorrecto para Frog");
	};
	lastDir = Vector2D<float>(0, 0);
	position = Vector2D<float>(pointX, pointY);
	game->setFrogSpawn(pointX, pointY);
	this->health = health;
	texture = this->texture = game->getGame()->getTexture(game->getGame()->FROG);
	std::cout << "Vidas restantes: " << health << std::endl;
}

void Frog::Render() const {
	SDL_FRect frogDimensions = getBoundingBox();
	frogDimensions.x = position.GetX();
	frogDimensions.y = position.GetY();
	SDL_FPoint center = { frogDimensions.w / 2, frogDimensions.h / 2 };
	texture->renderFrame(frogDimensions, 0, anim, angle, &center, SDL_FLIP_NONE);
}

void Frog::FrogMovementUpdateInstJump() {
	//Movimiento
	const float step = FROG_STEP;
	static int jumpFrames = 0;
	if (lastDir.GetX() != 0 || lastDir.GetY() != 0) {
		float newX = position.GetX() + lastDir.GetX() * step;
		float newY = position.GetY() + lastDir.GetY() * step;
		bool outD = newX > game->getGame()->WINDOW_WIDTH - texture->getFrameWidth(),
			outL = newX < 0,
			outR = newY > game->getFrogSpawn().GetY();

		if (outL) {
			position = Point2D<float>(0, position.GetY());
		}
		else if (outD) {
			position = Point2D<float>(game->getGame()->WINDOW_WIDTH - texture->getFrameWidth(), position.GetY());
		}
		else if (outR) {
			position = Point2D<float>(position.GetX(), game->getFrogSpawn().GetY());
		}
		else {
			position = position + lastDir * step;
		}
		if (!outD && !outL && !outR) {
		jumpFrames = JUMP_DURATION;
		anim = 1;
		}
		lastDir = Vector2D<float>(0, 0);
	}
	else {
		jumpFrames--;
		if (jumpFrames == 0) anim = 0;
	}
}

void Frog::FrogMovementUpdateAnimJump() {
	const float step = FROG_STEP;
	float newX = position.GetX() + lastDir.GetX() * step;
	float newY = position.GetY() + lastDir.GetY() * step;

}

void Frog::FrogCollisionsUpdate() {
	//Colisiones
	SDL_FRect hitbox = { position.GetX() + FROG_HITBOX_OFFSET_X, position.GetY() + FROG_HITBOX_OFFSET_Y, FROG_HITBOX_WIDTH, FROG_HITBOX_HEIGHT }; //Calculado con los espacios de píxeles entre límite de textura y de rana
	Collision col = game->checkCollision(hitbox);
	if (position.GetX() > game->getGame()->WINDOW_WIDTH || position.GetX() < -texture->getFrameWidth()) {
		health--;
		std::cout << "Vidas restantes: " << health << std::endl;
		position = game->getFrogSpawn();
		angle = 0;
	}
	else if (col.tipo == PLATFORM) {
		position = position + col.speed * (game->getGame()->FRAME_RATE / 1000.0);
	}
	else if (col.tipo == HOME) {
		if (game->tryReachHome(hitbox)) {
			health--;
			std::cout << "Vidas restantes: " << health << std::endl;
		}
		position = game->getFrogSpawn();
	}
	else if (col.tipo == ENEMY || position.GetY() < game->RIVER_LOW) {
		health--;
		std::cout << "Vidas restantes: " << health << std::endl;
		if (health > 0) {
			position = game->getFrogSpawn();
			angle = 0;
		}
	}
}

void Frog::Update() {
	FrogMovementUpdateInstJump();
	FrogCollisionsUpdate();
}

void Frog::handleEvent(const SDL_Event& event) {
	if (event.type == SDL_EVENT_KEY_DOWN) {
		switch (event.key.key) {
		case SDLK_W: case SDLK_UP:
			lastDir = Vector2D<float>(0, -1);
			angle = ANGLE_UP;
			break;
		case SDLK_A: case SDLK_LEFT:
			lastDir = Vector2D<float>(-1, 0);
			angle = ANGLE_LEFT;
			break;
		case SDLK_S: case SDLK_DOWN:
			lastDir = Vector2D<float>(0, 1);
			angle = ANGLE_DOWN;
			break;
		case SDLK_D: case SDLK_RIGHT:
			lastDir = Vector2D<float>(1, 0);
			angle = ANGLE_RIGHT;
			break;
		default:
			break;
		}
	}
	else if (event.type == SDL_EVENT_KEY_UP) {
		lastDir = Vector2D<float>(0, 0);
	}
}

int Frog::getLives() const {
	return health;
}
