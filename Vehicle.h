#pragma once
//#include "src/game.h"
#include "src/texture.h"
#include "Vector2D.h"
#include "Collision.h"

class Game;
class Vehicle
{
private:
	Game* game;
	Texture* texture;
	Point2D<int> position;
	Vector2D<int> speed;
	SDL_FRect hitbox;

public:
	Vehicle(Vector2D<int> sentido, Point2D<int> posicion, Texture* textura, Game* game);

	void Render() const;
	void Update();
	Collision CheckCollision(const SDL_FRect& FRect);
};

