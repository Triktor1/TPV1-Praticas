#include "Vehicle.h"
#include "src/texture.h"

Vehicle::Vehicle(Vector2D<int> sentido, Point2D<int> posicion, Texture* textura, Game* game) {
	Vehicle::speed = sentido;
	Vehicle::position = posicion;
	Vehicle::texture = textura;
	Vehicle::game = game;
}


Vector2D<int> GetVehicleSpeed() {

}

Texture* GetVehicleTexture() {

}
Collision CheckCollision(const SDL_FRect& FRect) {
	SDL_FRect vehicleRect;
	SDL_HasRectIntersectionFloat(&FRect, &vehicleRect);
}
