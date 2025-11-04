#pragma once
#include "texture.h"
#include "Vector2D.h"
#include "Collision.h"
#include "SceneObject.h"

class Game;

class HomedFrog : public SceneObject
{
private:
	Game* game;
	Texture* texture;
	Point2D<float> position;
	bool reached;
public:

	HomedFrog(Point2D<float>, Texture*, Game*);
	void Render() const override;
	Collision CheckCollision(const SDL_FRect& FRect);
	void SetReached(bool hasReached);
	bool GetReached() const;
};
