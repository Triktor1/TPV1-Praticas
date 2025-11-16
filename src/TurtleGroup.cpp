#include "TurtleGroup.h"

TurtleGroup::TurtleGroup(Point2D<float> position, Vector2D<float> speed, int numTurtles, bool submergible, Texture* texture, Game* game) :
	Platform(position, speed, texture, game),
	numTurtles(numTurtles),
	submergible(submergible)
{
}

TurtleGroup::TurtleGroup(Game* game, std::istream& file) :
	Platform(game, file)
{
	float posX, posY, speedX;
	int numTurtles, submergible;
	file >> posX >> posY >> speedX >> numTurtles >> submergible;
	this->position = Vector2D<float>(posX, posY);
	this->speed = Vector2D<float>(speedX, 0);
	this->texture = game->getTexture(game->TURTLE);
	this->numTurtles = numTurtles;
	this->submergible = submergible == 1;
}

void TurtleGroup::Render() const {
	float turtlesWidth = (float)texture->getFrameWidth();
	for (int i = 0; i < numTurtles; i++) {
		SDL_FRect hitbox = {
			position.GetX() + i * texture->getFrameWidth(),
			position.GetY(), texture->getFrameWidth(), texture->getFrameHeight() };
		Point2D<float> pos(position.GetX() + i * turtlesWidth, position.GetY());
		texture->renderFrame(hitbox, 0, 0);
	}
}

Collision TurtleGroup::checkCollision(const SDL_FRect& FRect) const {
	Collision collision;
	SDL_FRect col{ position.GetX(), position.GetY(), (float)texture->getFrameWidth() * numTurtles, (float)texture->getFrameHeight() };
	if (SDL_HasRectIntersectionFloat(&FRect, &col)) {
		collision.tipo = PLATFORM;
		collision.speed = speed;
	}
	else collision.tipo = NONE;

	return collision;
}
