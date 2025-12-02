#pragma once
#include "SceneObject.h"
#include "EventHandler.h"

class Frog : public SceneObject, public EventHandler
{
private:
	// 448/14, osea 14 pasos (y además la altura de un tile en píxeles)
	static constexpr int FROG_STEP = 32; 
	
	//Dimensiones y desplazamiento de la hitbox de la rana
	static constexpr float FROG_HITBOX_OFFSET_X = 5.5f;
	static constexpr float FROG_HITBOX_OFFSET_Y = 8.5f;
	static constexpr float FROG_HITBOX_WIDTH = 25.0f;
	static constexpr float FROG_HITBOX_HEIGHT = 19.0f;

	//Angulo de la direccin en la que mira la rana
	static constexpr float ANGLE_UP = 0.0f;
	static constexpr float ANGLE_RIGHT = 90.0f;
	static constexpr float ANGLE_DOWN = 180.0f;
	static constexpr float ANGLE_LEFT = 270.0f;

	// Frames que dura la animación de salto de la rana
	static constexpr int JUMP_DURATION = 7; 


	Point2D<float> position;
	Vector2D<float> lastDir;
	int health;
	int anim;
	double angle;

	void FrogMovementUpdateInstJump();
	void FrogMovementUpdateAnimJump();
	void FrogCollisionsUpdate();

public:
	
	void handleEvent(const SDL_Event& e) override;
	Frog(Vector2D<float>, Point2D<float>, int, Texture*, PlayState*);
	Frog(PlayState*, std::istream&);
	void Render() const override;
	void Update() override;
	int getLives() const;
};
