#pragma once
#include <SDL3/SDL.h>
#include <list>
#include <functional> 

class GameObject;
class EventHandler;
class Game;
class GameState
{
private:
	using DelayedCallback = std::function<void()>;
	std::list<GameObject*> gameObjects;
	std::list<EventHandler*> eventHandlers;
	std::list<DelayedCallback> delayedCallbacks;
protected:
	Game* game;
public:
	void render() const;
	void update();
	void handleEvent(const SDL_Event&);
};

