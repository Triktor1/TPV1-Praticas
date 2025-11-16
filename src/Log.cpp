#include "Log.h"

Log::Log(Vector2D<float> sentido, Point2D<float> posicion, Texture* textura, Game* juego) :
	Platform(posicion, sentido, textura, juego)
{
}

Log::Log(Game* game, std::istream& file) :
	Platform(game, file)
{
	float posX, posY, speedX, textureType;
	file >> posX >> posY >> speedX >> textureType;
	this->position = Vector2D<float>(posX, posY);
	this->speed = Vector2D<float>(speedX, 0);
	this->texture = game->getTexture(Game::TextureName(game->LOG1 + textureType));
}

void Log::Render() const {
	SDL_FRect hitbox = { (float)position.GetX(), (float)position.GetY(),
				(float)texture->getFrameWidth(), (float)texture->getFrameHeight() };
	texture->renderFrame(hitbox, 0, 0);
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
