#include "Vehicle.h"
#include "Game.h"

Vehicle::Vehicle(Vector2D<float> sentido, Point2D<float> posicion, Texture* textura, Game* juego) :
	Crosser(posicion, sentido, textura, juego)
{
}

void Vehicle::Update() {
	position = position + speed * (game->FRAME_RATE / 1000.0);
	if (position.GetX() < -150) position = { position.GetX() + 150 + game->WINDOW_WIDTH , position.GetY() };
	else if (position.GetX() > game->WINDOW_WIDTH) position = { position.GetX() - 150 - game->WINDOW_WIDTH, position.GetY() };
}

Collision Vehicle::CheckCollision(const SDL_FRect& FRect) {
	return Collision();
}

Vehicle* Vehicle::readFile(std::istream& file) {
	int pointX, pointY, directionX, c_sprType;
	
	if (!(file >> pointX >> pointY >> directionX >> c_sprType)) {
		throw string("Error: formato invalido para vehiculo.\n");
	}

	switch (c_sprType) {
	case '1': sprType = CAR1; break;
	case '2': sprType = CAR2; break;
	case '3': sprType = CAR3; break;
	case '4': sprType = CAR4; break;
	case '5': sprType = CAR5; break;
	default:  sprType = CAR1; break;
	}
	return new Vehicle{ Vector2D<float>(directionX, 0), Point2D<float>(pointX, pointY), game->getTexture(game->CAR1), game };
}
