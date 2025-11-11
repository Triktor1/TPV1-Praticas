#include "Crosser.h"
#include "Game.h"

Crosser::Crosser(Point2D<float> position, Vector2D<float> speed, Texture* texture, Game* game) :
	SceneObject(position, texture, game),
	speed(speed)
{
}

void Crosser::Update() {
	position = position + speed * (game->FRAME_RATE / 1000.0);
	if (speed.GetX() > 0 && position.GetX() >= game->WINDOW_WIDTH + 150 - texture->getFrameWidth())
		position = {position.GetX() - 150 * 2 - game->WINDOW_WIDTH, position.GetY()};
	else if (position.GetX() < -150)
		 position = { position.GetX() + 150 + game->WINDOW_WIDTH , position.GetY() };
}

Vector2D<float> Crosser::getSpeed() const {
	return speed;
}
