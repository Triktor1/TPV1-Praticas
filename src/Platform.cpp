#include "Platform.h"

Collision Platform::checkCollision(const SDL_FRect& FRect) const{
	Collision collision;
	SDL_FRect hitbox = getBoundingBox();
	if (SDL_HasRectIntersectionFloat(&FRect, &hitbox)) {
		collision.tipo = PLATFORM;
		collision.speed = speed;
	}
	else collision.tipo = NONE;

	return collision;
}
