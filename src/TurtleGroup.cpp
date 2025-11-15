#include "TurtleGroup.h"

TurtleGroup::TurtleGroup(Point2D<float> position, Vector2D<float> speed, int numTurtles, bool submergible, Texture* texture, Game* game) :
	Platform(position, speed, texture, game),
	numTurtles(numTurtles),
	submergible(submergible)
{
}
