#pragma once
#include "SceneObject.h"

class Wasp : public SceneObject
{
private:
	Vector2D<float> speed;
	int lifeTime;
	Game::Anchor anchor;

public:
	Wasp(Point2D<float>, Vector2D<float>, Texture*, Game*, float);

	void Update();
	Collision CheckCollision(const SDL_FRect& FRect);

	//Comprueba si la avispa está viva o muerta
	bool isAlive() const;

	//Devuelve el tiempo de vida restante en segundos de la avispa
	int getLifeTime() const;

	//getter y setter del Anchor
	Game::Anchor getAnchor() const { return anchor; };
	void setAnchor(Game::Anchor it) { anchor = it; };
};

