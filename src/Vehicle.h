#pragma once
//#include "src/game.h"
#include "texture.h"
#include "Vector2D.h"
#include "Collision.h"
#include "game.h"

class Game;
class Collision;

class Vehicle
{
private:
	Game* game;
	Texture* texture;
	Point2D<int> position;
	Vector2D<int> speed;

public:
	Vehicle(Vector2D<int>, Point2D<int>, Texture*, Game*);

	void Render() const;
	void Update();
	Collision CheckCollision(const SDL_FRect& FRect);
};

