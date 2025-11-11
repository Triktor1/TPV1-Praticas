#include "Vehicle.h"
#include "Game.h"

Vehicle::Vehicle(Vector2D<float> sentido, Point2D<float> posicion, Texture* textura, Game* juego) : 
	Crosser(posicion, sentido, textura, juego)
{
}

void Vehicle::Update() {
	position = position + speed * (game->FRAME_RATE/1000.0);
	if (position.GetX() < -150) position = { position.GetX() + 150 + game->WINDOW_WIDTH , position.GetY() };
	else if (position.GetX() > game->WINDOW_WIDTH) position = { position.GetX() - 150 - game->WINDOW_WIDTH, position.GetY()};
}

Collision Vehicle::CheckCollision(const SDL_FRect& FRect) {
	Collision collision;
	SDL_FRect col{ position.GetX(), position.GetY(), texture->getFrameWidth(), texture->getFrameHeight() };
	if (SDL_HasRectIntersectionFloat(&FRect, &col))
		collision.tipo = ENEMY;
	else collision.tipo = NONE;
	
	return collision;
}
