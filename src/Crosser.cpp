#include "Crosser.h"
#include "Game.h"

Crosser::Crosser(Point2D<float> position, Vector2D<float> speed, Texture* texture, Game* game) :
	SceneObject(position, texture, game),
	speed(speed),
	backjump(150)
{
}

Crosser::Crosser(Game* game, std::istream& file) :
	SceneObject(game, file),
	backjump(150)
{
}

void Crosser::Update() {
	position = position + speed * (game->FRAME_RATE / 1000.0);
	if (speed.GetX() > 0) {
		if (position.GetX() >= game->WINDOW_WIDTH + backjump - texture->getFrameWidth()) {
			position = { position.GetX() - backjump * 2 - game->WINDOW_WIDTH, position.GetY() };
		}
	}
	else if (position.GetX() < -backjump) {
		position = { position.GetX() + backjump + game->WINDOW_WIDTH, position.GetY() };
	}
}

Collision Crosser::checkCollision(const SDL_FRect& FRect) const {
	return Collision();
}
