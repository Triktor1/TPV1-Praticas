#pragma once
#include "texture.h"
#include "Vector2D.h"
#include "Platform.h"
#include "game.h"

class TurtleGroup : public Platform
{
private:
	int numTurtles;
	bool submergible;
public:
	TurtleGroup(Point2D<float>, Vector2D<float>, int, bool, Texture*, Game*);
};
