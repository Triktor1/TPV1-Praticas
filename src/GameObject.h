#pragma once
#include <iostream>
#include <fstream>

class GameState;
class GameObject
{
public:
	virtual void Render() const = 0;
	virtual void Update() = 0;

protected:
	GameObject(GameState*);
	GameObject(GameState*, std::istream&);
	GameState* game;
public: 
	virtual ~GameObject() = default;
	GameState* getState() const { return game; }
};
