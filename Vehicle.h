#pragma once
//#include "src/game.h"
#include "src/texture.h"
#include "Vector2D.h"

class Game;
class Vehicle
{
private:
	Game* game;
	Texture* texture;
	Point2D position;
	Vector2D<int> speed;

public:
};

