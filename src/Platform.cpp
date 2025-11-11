#include "Platform.h"

Collision Platform::checkCollision(const SDL_FRect& FRect) {
	Collision collision;
	SDL_FRect hitbox = getBoundingBox();
	if (SDL_HasRectIntersectionFloat(&FRect, &hitbox)) {
		collision.tipo = PLATFORM;
		collision.speed = getSpeed();
	}
	else collision.tipo = NONE;

	return collision;
}
