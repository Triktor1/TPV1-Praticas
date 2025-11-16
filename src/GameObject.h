#pragma once
#include <istream>

class Game;
class GameObject
{
public:
	virtual void Render() const = 0;
	virtual void Update() = 0;

protected:
	Game* game;
	GameObject(Game*);
	GameObject(Game*, std::istream&);
	virtual ~GameObject();

};

