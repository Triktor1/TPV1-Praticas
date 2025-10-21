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
	if(reached) texture->renderFrame(frogDimensions, 0, 0);
}

void HomedFrog::SetReached(bool hasReached) {
	reached = hasReached;
}
