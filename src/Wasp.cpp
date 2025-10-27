#include "Wasp.h"

Wasp::Wasp(Point2D<float> position, Vector2D<float> speed, Texture* texture, Game* game, float lifeTime) :
	position(position),
	speed(speed),
	texture(texture),
	game(game),
	lifeTime(lifeTime)
{
}

void Wasp::Render() const {
	SDL_FRect hitbox = { (float)position.GetX(), (float)position.GetY(),
			(float)texture->getFrameWidth(), (float)texture->getFrameHeight() };
	texture->renderFrame(hitbox, 0, 0);
}

void Wasp::Update() {
	lifeTime -= game->FRAME_RATE;
}

Collision Wasp::CheckCollision(const SDL_FRect& FRect) {
	Collision collision;
	SDL_FRect col{ position.GetX(), position.GetY(), texture->getFrameWidth(), texture->getFrameHeight() };
	if (SDL_HasRectIntersectionFloat(&FRect, &col))
		collision.tipo = ENEMY;
	else collision.tipo = NONE;

	return collision;
}

bool Wasp::isAlive() const{
	return lifeTime >= 0;
}

int Wasp::getLifeTime() const {
	return lifeTime;
}
