#pragma once
#include "SceneObject.h"

class SDLApplication;
class Crosser : public SceneObject
{
protected:

	Vector2D<float> speed;
	int backjump;

public:
	Crosser(Point2D<float> position, Vector2D<float> speed, Texture* texture, PlayState* game);
	Crosser(PlayState*, std::istream&);
	void Update() override;
	virtual Collision checkCollision(const SDL_FRect& FRect) const override;
};
