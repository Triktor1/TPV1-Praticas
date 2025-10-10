#include "Vehicle.h"
#include "src/texture.h"

Vehicle::Vehicle(Vector2D<int> sentido, Point2D<int> posicion, Texture* textura, Game* juego) {
	speed = sentido;
	position = posicion;
	texture = textura;
	game = juego;
	hitbox = { (float)position.GetX(), (float)position.GetY(),
						(float)texture->getFrameWidth(), (float)texture->getFrameHeight() };
}
void Vehicle::Render() const {
	
}
void Vehicle::Update() {
	
}
Collision Vehicle::CheckCollision(const SDL_FRect& FRect) {
	Collision collision;
	SDL_FRect col{ position.GetX(), position.GetY(), texture->getFrameWidth(), texture->getFrameHeight() };
	if (SDL_HasRectIntersectionFloat(&FRect, &col))
		collision.tipo = ENEMY;
	else collision.tipo = NONE;
	
	return collision;
}
