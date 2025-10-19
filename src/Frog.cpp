#include "Frog.h"
#include "game.h"

using namespace std; 

Frog::Frog(Vector2D<float> lastDir, Point2D<float> position, int health, Texture* texture, Game* game) :
	lastDir(lastDir),
	position(position),
	health(health),
	texture(texture),
	game(game)
{
}

void Frog::Render() const {
	SDL_FRect hitbox = { position.GetX(), position.GetY(),
				(float)texture->getFrameWidth(), (float)texture->getFrameHeight() };
	texture->renderFrame(hitbox, 0, 0);
}

void Frog::Update() {
	const float step = 1070.50f;
	float maxX = Game::WINDOW_WIDTH - (float)texture->getFrameWidth();
	float maxY = Game::WINDOW_HEIGHT - (float)texture->getFrameHeight();
	if (lastDir.GetX() != 0 || lastDir.GetY() != 0) {
		float newX = position.GetX() + lastDir.GetX() * step * (game->FRAME_RATE / 1000.0);
		float newY = position.GetY() + lastDir.GetY() * step * (game->FRAME_RATE / 1000.0);
		if (newX >= 0 && newX <= maxX &&
			newY >= 0 && newY <= maxY)
		{
			position = position + lastDir * step * (game->FRAME_RATE / 1000.0);

		}
		lastDir = Vector2D<float>(0, 0);
	}
	std::cout << position.GetX() << " " << position.GetY() << std::endl;
}

void Frog::HandleEvent(const SDL_Event& event) {
	if (event.type == SDL_EVENT_KEY_DOWN) {
		switch (event.key.key) {
		case SDLK_W:
			lastDir = Vector2D<float>(0, -1);
			break;
		case SDLK_A:
			lastDir = Vector2D<float>(-1, 0);
			break;
		case SDLK_S:
			lastDir = Vector2D<float>(0, 1);
			break;
		case SDLK_D:
			lastDir = Vector2D<float>(1, 0);
			break;
		default:
			break;
		}
	}
	else if (event.type == SDL_EVENT_KEY_UP) {
		lastDir = Vector2D<float>(0, 0);
	}
}
