#include "Frog.h"
#include "game.h"

using namespace std;

Frog::Frog(Vector2D<float> lastDir, Point2D<float> position, int health, Texture* texture, Game* game) :
	lastDir(lastDir),
	position(position),
	health(health),
	texture(texture),
	game(game),
	anim(0),
	angle(0.0)
{
}

void Frog::Render() const {
	SDL_FRect frogDimensions = { position.GetX(), position.GetY(),
				(float)texture->getFrameWidth(), (float)texture->getFrameHeight() };
	SDL_FPoint center = { frogDimensions.w / 2, frogDimensions.h / 2 };
	texture->renderFrame(frogDimensions, 0, anim, angle, &center, SDL_FLIP_NONE);
}

void Frog::Update() {
	//Movimiento
	const float step = 1070.50f;
	static int jumpFrames = 0;
	float maxX = Game::WINDOW_WIDTH - (float)texture->getFrameHeight();
	float maxY = Game::WINDOW_HEIGHT - (float)texture->getFrameHeight();
	if (lastDir.GetX() != 0 || lastDir.GetY() != 0) {
		float newX = position.GetX() + lastDir.GetX() * step * (game->FRAME_RATE / 1000.0);
		float newY = position.GetY() + lastDir.GetY() * step * (game->FRAME_RATE / 1000.0);
		if (newX >= 0 && newX <= maxX &&
			newY >= 0 && newY <= maxY)
		{
			anim = 1;
			position = position + lastDir * step * (game->FRAME_RATE / 1000.0);
			jumpFrames = 7;
		}
		lastDir = Vector2D<float>(0, 0);
	}
	else {
		jumpFrames--;
		if (jumpFrames == 0) anim = 0;
	}
	//std::cout << position.GetX() << " " << position.GetY() << std::endl;

	//Colisiones
	SDL_FRect hitbox = { position.GetX() + 5.5, position.GetY() + 8.5, 25, 19 };
	Collision col = game->checkCollision(hitbox);
	switch (col.tipo) {
	case ENEMY:
		health--;
		position = Point2D<float>(0, 0);
		break;
	case PLATFORM:
		position = position + col.speed * (game->FRAME_RATE / 1000.0);
		break;
	case HOME:
		break;
	default:
		break;
	}
}

void Frog::HandleEvent(const SDL_Event& event) {
	if (event.type == SDL_EVENT_KEY_DOWN) {
		switch (event.key.key) {
		case SDLK_W: case SDLK_UP:
			lastDir = Vector2D<float>(0, -1);
			angle = 0;
			break;
		case SDLK_A: case SDLK_LEFT:
			lastDir = Vector2D<float>(-1, 0);
			angle = 270;
			break;
		case SDLK_S: case SDLK_DOWN:
			lastDir = Vector2D<float>(0, 1);
			angle = 180;
			break;
		case SDLK_D: case SDLK_RIGHT:
			lastDir = Vector2D<float>(1, 0);
			angle = 90;
			break;
		default:
			break;
		}
	}
	else if (event.type == SDL_EVENT_KEY_UP) {
		lastDir = Vector2D<float>(0, 0);
	}
}

