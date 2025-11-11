#include "TurtleGroup.h"

TurtleGroup::TurtleGroup(Point2D<float> position, Vector2D<float> speed, int turtleNum, bool submergible, Texture* texture, Game* game) :
	Platform(position, speed, texture, game),
	turtleNum(turtleNum),
	submergible(submergible)
{
}
