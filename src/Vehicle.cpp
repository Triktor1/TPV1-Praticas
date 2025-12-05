#include "Vehicle.h"
#include "GameError.h"
#include "playState.h"
#include "SDLApplication.h"
#include <string>

Vehicle::Vehicle(Vector2D<float> sentido, Point2D<float> posicion, Texture* textura, PlayState* juego) :
	Crosser(posicion, sentido, textura, juego)
{
	this->game = game;
}

Vehicle::Vehicle(PlayState* game, std::istream& file) :
	Crosser(game, file)
{
	this->game = game;
	float posX, posY, speedX, textureType;
	if (!(file >> posX >> posY >> speedX >> textureType)) {
		throw GameError("Formato Incorrrecto/incompleto de Vehicle");
	}
	this->texture = game->getGame()->getTexture(SDLApplication::TextureName(game->getGame()->CAR1 + textureType - 1));
	this->position = Vector2D<float>(posX, posY);
	this->speed = Vector2D<float>(speedX, 0);
}
void Vehicle::Render() const {
	SDL_FlipMode flip = (speed.GetX() > 0) ? SDL_FLIP_NONE : SDL_FLIP_VERTICAL;
	texture->renderFrame(getBoundingBox(), 0, 0, flip);
}

Collision Vehicle::checkCollision(const SDL_FRect& FRect) const {
	Collision colision;
	colision.speed = Vector2D<float>(0, 0);
	colision.tipo = NONE;
	SDL_FRect hitbox = getBoundingBox();
	if (SDL_HasRectIntersectionFloat(&FRect, &hitbox)) {
		colision.tipo = ENEMY;
	}
	return colision;
}
