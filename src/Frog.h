#pragma once
#include "texture.h"
#include "Vector2D.h"
#include "Collision.h"
#include "game.h"

class Game;
class Collision;

class Frog
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

	Game* game;
	Texture* texture;
	Point2D<float> position;
	Vector2D<float> lastDir;
	int anim;
	int health;
	double angle;

	void FrogMovementUpdate();
	void FrogCollisionsUpdate();

public:
	
	Frog(Vector2D<float>, Point2D<float>, int, Texture*, Game*);
	void Render() const;
	void Update();
	void HandleEvent(const SDL_Event&);
	int GetHealth() const;
};
