#pragma once
#include "GameObject.h"
#include "texture.h"
#include "Vector2D.h"
#include "Collision.h"

class PlayState;
class SceneObject : public GameObject
{
protected:
	Point2D<float> position;
	float height, width;
	Texture* texture;
	SDL_FRect getBoundingBox() const;
	PlayState* game;
public:
	SceneObject(Point2D<float>, Texture*, PlayState*);
	SceneObject(PlayState*, std::istream&);
	virtual void Render() const override;
	void Update() override;
	virtual Collision checkCollision(const SDL_FRect&) const;
};
