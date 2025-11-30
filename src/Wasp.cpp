#include "Wasp.h"

Wasp::Wasp(Point2D<float> position, Vector2D<float> speed, Texture* texture, SDLApplication* game, float lifeTime) :
	SceneObject(position, texture, game),
	speed(speed),
	lifeTime(lifeTime)
{
}

Wasp::Wasp(SDLApplication* game, std::istream& file) :
	SceneObject(game, file)
{
	float posX, posY, speedX, speedY, time;
	file >> posX >> posY >> speedX >> speedY >> time;
	position = Vector2D<float>(posX, posY);
	speed = Vector2D<float>(speedX, speedY);
	lifeTime = time;
	texture = this->texture = game->getTexture(game->WASP);
}

void Wasp::Update() {
	lifeTime -= game->FRAME_RATE;
	if (!isAlive()) game->deleteAfter(anchor);
}

Collision Wasp::checkCollision(const SDL_FRect& FRect) const {
	Collision collision;
	SDL_FRect col{ position.GetX(), position.GetY(), texture->getFrameWidth(), texture->getFrameHeight() };
	if (SDL_HasRectIntersectionFloat(&FRect, &col))
		collision.tipo = ENEMY;
	else collision.tipo = NONE;

	return collision;
}

bool Wasp::isAlive() const {
	return lifeTime >= 0;
}

int Wasp::getLifeTime() const {
	return lifeTime;
}
