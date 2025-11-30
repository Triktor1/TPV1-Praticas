#pragma once
#include <iostream>
#include <fstream>
#include "game.h"

class GameObject
{
public:
	virtual void Render() const = 0;
	virtual void Update() = 0;

protected:
	SDLApplication* game;
	GameObject(SDLApplication*);
	GameObject(SDLApplication*, std::istream&);
	virtual ~GameObject();
	GameState* state;

//Es él quien ahora se encargar de devolver el 
public: 
	GameState* getState() const { return state; }
};

