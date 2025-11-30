#include "Log.h"
#include "GameError.h"
Log::Log(Vector2D<float> sentido, Point2D<float> posicion, Texture* textura, SDLApplication* juego) :
	Platform(posicion, sentido, textura, juego)
{
}

Log::Log(SDLApplication* game, std::istream& file) :
	Platform(game, file)
{
	float posX, posY, speedX, textureType;
	if (!(file >> posX >> posY >> speedX >> textureType)) {
		throw GameError("Formato invalido Log");
	}
	this->position = Vector2D<float>(posX, posY);
	this->speed = Vector2D<float>(speedX, 0);
	this->texture = game->getTexture(SDLApplication::TextureName(game->LOG1 + textureType));
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
