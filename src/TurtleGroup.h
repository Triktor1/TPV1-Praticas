#pragma once
#include "Platform.h"

class TurtleGroup : public Platform
{
private:
	int numTurtles;
	bool submergible;
	int GetCurrentAnim() const;

public:
	TurtleGroup(Point2D<float>, Vector2D<float>, int, bool, Texture*, PlayState*);
	TurtleGroup(PlayState*, std::istream&);
	void Render() const override;
	Collision checkCollision(const SDL_FRect& FRect) const override;
};
