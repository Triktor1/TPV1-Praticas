#include "Frog.h"



Frog::Frog(Vector2D<float> lastDir, Point2D<float> position, int health, Texture* texture, Game* game) :
	SceneObject(position, texture, game),
	lastDir(lastDir),
	health(health),
	anim(0),
	angle(0.0)
{
}

Frog::Frog(Game* game, std::istream& file) : 
	SceneObject(game, file),
	anim(0),
	angle(0.0)
{
	float pointX, pointY;
	int health;
	if (!(file >> pointX >> pointY >> health)) {
		throw std::string("Error: formato invalido para rana.\n");
	};
	lastDir = Vector2D<float>(0, 0);
	position = Vector2D<float>(pointX, pointY);
	game->setFrogSpawn(pointX, pointY);
	this -> health = healthfile;
	texture = this->texture = game->getTexture(game->FROG);
}


void Frog::Render() const {
	SDL_FRect frogDimensions = { position.GetX(), position.GetY(),
				(float)texture->getFrameWidth(), (float)texture->getFrameHeight() };
	SDL_FPoint center = { frogDimensions.w / 2, frogDimensions.h / 2 };
	texture->renderFrame(frogDimensions, 0, anim, angle, &center, SDL_FLIP_NONE);
}

void Frog::FrogMovementUpdate() {
	//Movimiento
	const float step = FROG_STEP;
	static int jumpFrames = 0;
	float maxX = Game::WINDOW_WIDTH - (float)texture->getFrameHeight();
	float maxY = Game::WINDOW_HEIGHT - (float)texture->getFrameHeight();
	if (lastDir.GetX() != 0 || lastDir.GetY() != 0) {
		float newX = position.GetX() + lastDir.GetX() * step;
		float newY = position.GetY() + lastDir.GetY() * step;
		if (newX < 0) {
			position = Point2D<float>(0, position.GetY());
		}
		else if (newX > game->WINDOW_WIDTH - texture->getFrameWidth()) {
			position = Point2D<float>(game->WINDOW_WIDTH - texture->getFrameWidth(), position.GetY());
		}
		else if (newY > game->getFrogSpawn().GetY() + step) {
			position = Point2D<float>(position.GetX(), game->getFrogSpawn().GetY() + step);
		}
		else {
			position = position + lastDir * step;
		}
		anim = 1;
		jumpFrames = JUMP_DURATION;
		lastDir = Vector2D<float>(0, 0);
	}
	else {
		jumpFrames--;
		if (jumpFrames == 0) anim = 0;
	}
}

void Frog::FrogCollisionsUpdate() {
	//Colisiones
	SDL_FRect hitbox = { position.GetX() + FROG_HITBOX_OFFSET_X, position.GetY() + FROG_HITBOX_OFFSET_Y, FROG_HITBOX_WIDTH, FROG_HITBOX_HEIGHT }; //Calculado con los espacios de píxeles entre límite de textura y de rana
	Collision col = game->checkCollision(hitbox);
	if (col.tipo == PLATFORM) {
		position = position + col.speed * (game->FRAME_RATE / 1000.0);
	}
	else if (col.tipo == HOME) {
		if (game->tryReachHome(hitbox)) {
			health--;
		}
		position = game->getFrogSpawn();
	}
	else if (col.tipo == ENEMY || position.GetY() < game->RIVER_LOW || position.GetX() > game->WINDOW_WIDTH - texture->getFrameWidth()) {
		health--;
		position = game->getFrogSpawn();
		angle = 0;
	}
}

void Frog::Update() {
	FrogMovementUpdate();
	FrogCollisionsUpdate();
}

void Frog::HandleEvent(const SDL_Event& event) {
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
