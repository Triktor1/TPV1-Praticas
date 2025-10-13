#include "Vehicle.h"
#include "src/texture.h"


Vehicle::Vehicle(Vector2D<int> sentido, Point2D<int> posicion, Texture* textura, Game* juego) :
	speed(sentido),
	position(posicion),
	texture(textura),
	game(juego)
{

}

void Vehicle::Render() const {
	SDL_FRect hitbox = { (float)position.GetX(), (float)position.GetY(),
				(float)texture->getFrameWidth(), (float)texture->getFrameHeight() };
	texture->renderFrame(hitbox, 0, 0);
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
