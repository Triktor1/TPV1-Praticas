#pragma once

class Game;
class GameObject
{
private:
	Game* game;
public:
	virtual void Render() const = 0;
	virtual void Update() = 0;
	virtual ~GameObject();

protected:
	GameObject(Game*);

};

