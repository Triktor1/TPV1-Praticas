#include "Vehicle.h"
#include "src/texture.h"

Vehicle::Vehicle(Vector2D<int> sentido, Point2D<int> posicion, Texture* textura, Game* game) {
	Vehicle::speed = sentido;
	Vehicle::position = posicion;
	Vehicle::texture = textura;
	Vehicle::game = game;
	Vehicle::hitbox = { (float)position.GetX(), (float)position.GetY(),
						(float)texture->getFrameWidth(), (float)texture->getFrameHeight() };
}

Collision CheckCollision(const SDL_FRect& FRect) {
	Collision collision;

	if (SDL_HasRectIntersectionFloat(&FRect, &vehicleRect))
		collision.tipo = ENEMY;
	else collision.tipo = NONE;
	
	return collision;
}
