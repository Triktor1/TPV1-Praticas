#pragma once
#include "SceneObject.h"

class Wasp : public SceneObject
{
private:
	Vector2D<float> speed;
	int lifeTime;
	SDLApplication::Anchor anchor;

public:
	Wasp(Point2D<float>, Vector2D<float>, Texture*, SDLApplication*, float);
	Wasp(SDLApplication*, std::istream&);

	void Update() override;
	Collision checkCollision(const SDL_FRect&) const override; 
	//Comprueba si la avispa está viva o muerta
	bool isAlive() const;

	//Devuelve el tiempo de vida restante en segundos de la avispa
	int getLifeTime() const;

	//getter y setter del Anchor
	SDLApplication::Anchor getAnchor() const { return anchor; };
	void setAnchor(const SDLApplication::Anchor& it) { anchor = it; };
};

