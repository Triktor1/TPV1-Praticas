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
	
	// Frames que dura la animación de salto de la rana
	static constexpr int JUMP_DURATION = 7; 

	Game* game;
	Texture* texture;
	Point2D<float> position;
	Vector2D<float> lastDir;
	int anim;
	int health;
	double angle;

public:
	//Vidas de la rana
	static constexpr int HEALTH = 3;
	
	Frog(Vector2D<float>, Point2D<float>, int, Texture*, Game*);
	void Render() const;
	void Update();
	void HandleEvent(const SDL_Event&);
	int GetHealth() const;
};
