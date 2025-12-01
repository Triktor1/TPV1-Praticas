#pragma once
#include "SceneObject.h"
#include "PlayState.h"

class Wasp : public SceneObject
{
private:
	Vector2D<float> speed;
	int lifeTime;
	GameState::Anchor anchorGS;
	PlayState::Anchor anchorPS;

public:
	Wasp(Point2D<float>, Vector2D<float>, Texture*, PlayState*, float);
	Wasp(PlayState*, std::istream&);

	void Update() override;
	Collision checkCollision(const SDL_FRect&) const override; 
	//Comprueba si la avispa está viva o muerta
	bool isAlive() const;

	//Devuelve el tiempo de vida restante en segundos de la avispa
	int getLifeTime() const;

	//getter y setter del Anchor
	PlayState::Anchor getAnchorPS() const { return anchorPS; };
	GameState::Anchor getAnchorGS() const { return anchorGS; };
	void setAnchorPS(const PlayState::Anchor& it) { anchorPS = it;};
	void setAnchorGS(const GameState::Anchor& it) { anchorGS = it; };
};
