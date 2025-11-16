#include "Vehicle.h"
#include "Game.h"
#include <string>

Vehicle::Vehicle(Vector2D<float> sentido, Point2D<float> posicion, Texture* textura, Game* juego) :
	Crosser(posicion, sentido, textura, juego)
{
}

Vehicle::Vehicle(Game* game,std::istream& file) :
	Crosser(game, file)
{
	float posX, posY, speedX, textureType;
	if (!(file >> posX >> posY >> speedX >> textureType)) {
		//throw string("Error: formato invalido para vehiculo.\n");
	}
	this->position = Vector2D<float>(posX, posY);
	this->speed = Vector2D<float>(speedX, 0);
	this->texture = game->getTexture(Game::TextureName(game->CAR1 + textureType - 1));
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
