#include "Log.h"
#include "GameError.h"
#include "PlayState.h"
#include "SDLApplication.h"

Log::Log(Vector2D<float> sentido, Point2D<float> posicion, Texture* textura, PlayState* juego) :
	Platform(posicion, sentido, textura, juego)
{
	this->game = game;
}

Log::Log(PlayState* game, std::istream& file) :
	Platform(game, file)
{
	this->game = game;
	float posX, posY, speedX, textureType;
	if (!(file >> posX >> posY >> speedX >> textureType)) {
		throw GameError("Formato invalido Log");
	}
	this->position = Vector2D<float>(posX, posY);
	this->speed = Vector2D<float>(speedX, 0);
	this->texture = game->getGame()->getTexture(SDLApplication::TextureName(game->getGame()->LOG1 + textureType));
}

Collision Log::checkCollision(const SDL_FRect& FRect) const {
	Collision collision;
	SDL_FRect col{ position.GetX(), position.GetY(), (float)texture->getFrameWidth(), (float)texture->getFrameHeight() };
	if (SDL_HasRectIntersectionFloat(&FRect, &col)) {
		collision.tipo = PLATFORM;
		collision.speed = speed;
	}
	else collision.tipo = NONE;

	return collision;
}
