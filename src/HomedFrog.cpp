#include "HomedFrog.h"

HomedFrog::HomedFrog(Point2D<float> position, Texture* texture, PlayState* game) :
	SceneObject(position, texture, game),
	reached(false)
{
}

void HomedFrog::Render() const {
	SDL_FRect frogDimensions =  getBoundingBox();
	SDL_FPoint center = { frogDimensions.w / 2, frogDimensions.h / 2 };
	if (reached) {
		texture->renderFrame(frogDimensions, 0, 0, 180, &center, SDL_FLIP_NONE);
	}
}

Collision HomedFrog::checkCollision(const SDL_FRect& FRect) const {
	Collision collision;
	SDL_FRect col = getBoundingBox();
	if (SDL_HasRectIntersectionFloat(&FRect, &col)) {
		collision.tipo = HOME;
	}
	else collision.tipo = NONE;

	return collision;
}


void HomedFrog::SetReached(bool hasReached) {
	reached = hasReached;
}

bool HomedFrog::GetReached() const {
	return reached;
}
