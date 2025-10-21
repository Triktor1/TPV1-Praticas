#include "HomedFrog.h"
#include "game.h"

HomedFrog::HomedFrog(Point2D<float> position, Texture* texture, Game* game) :
	position(position),
	texture(texture),
	game(game),
	reached(false)
{
}

void HomedFrog::Render() const {
	SDL_FRect frogDimensions = { position.GetX(), position.GetY(),
			(float)texture->getFrameWidth(), (float)texture->getFrameHeight() };
	SDL_FPoint center = { frogDimensions.w / 2, frogDimensions.h / 2 };
	if(reached) texture->renderFrame(frogDimensions, 0, 0, 180, &center, SDL_FLIP_NONE);
}

Collision HomedFrog::CheckCollision(const SDL_FRect& FRect) {
	Collision collision;
	SDL_FRect col{ position.GetX(), position.GetY(), (float)texture->getFrameWidth(), (float)texture->getFrameHeight() };
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
