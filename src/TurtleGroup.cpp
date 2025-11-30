#include "TurtleGroup.h"
#include "GameError.h"

TurtleGroup::TurtleGroup(Point2D<float> position, Vector2D<float> speed, int numTurtles, bool submergible, Texture* texture, SDLApplication* game) :
	Platform(position, speed, texture, game),
	numTurtles(numTurtles),
	submergible(submergible)
{
}

constexpr const int SUBMERGETIME = 300;

TurtleGroup::TurtleGroup(SDLApplication* game, std::istream& file) :
	Platform(game, file)
{
	float posX, posY, speedX;
	int numTurtles, submergible;
	if (!(file >> posX >> posY >> speedX >> numTurtles >> submergible)) {
		throw GameError("Formato Invalido para Turtle");
	}
	this->position = Vector2D<float>(posX, posY);
	this->speed = Vector2D<float>(speedX, 0);
	this->texture = game->getTexture(game->TURTLE);
	this->numTurtles = numTurtles;
	this->submergible = submergible == 1;
}

int TurtleGroup::GetCurrentAnim() const {
	int frames = submergible ? 7 : 2;
	int now = SDL_GetTicks(); 
	int frame = ((now / SUBMERGETIME)) % frames;
	return frame;
}

void TurtleGroup::Render() const {
	float turtlesWidth = (float)texture->getFrameWidth();
	int anim = GetCurrentAnim();
	SDL_FlipMode flip = (speed.GetX() < 0) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
	for (int i = 0; i < numTurtles; i++) {
		SDL_FRect hitbox = {
			position.GetX() + i * texture->getFrameWidth(),
			position.GetY(), texture->getFrameWidth(), texture->getFrameHeight() };
		Point2D<float> pos(position.GetX() + i * turtlesWidth, position.GetY());
		texture->renderFrame(hitbox, 0, anim, flip);
	}
}

Collision TurtleGroup::checkCollision(const SDL_FRect& FRect) const {
	Collision collision;
	int anim = GetCurrentAnim();
	SDL_FRect col{ position.GetX(), position.GetY(), (float)texture->getFrameWidth() * numTurtles, (float)texture->getFrameHeight() };
	if (SDL_HasRectIntersectionFloat(&FRect, &col)) {
		if (submergible && anim >= 5 && anim <= 6) {
			collision.tipo = NONE; 
		}
		else {
			collision.tipo = PLATFORM;
			collision.speed = speed;
		}
	}
	else collision.tipo = NONE;

	return collision;
}
