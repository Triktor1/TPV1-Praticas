#pragma once
#include "SceneObject.h"

class HomedFrog : public SceneObject
{
private:
	bool reached;
public:

	HomedFrog(Point2D<float>, Texture*, PlayState*);
	void Render() const override;
	Collision checkCollision(const SDL_FRect& FRect) const override;
	void SetReached(bool hasReached);
	bool GetReached() const;
};
