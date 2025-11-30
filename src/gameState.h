#pragma once
#include <SDL3/SDL.h>
#include <list>
#include <functional> 

class GameObject;
class EventHandler;
class SDLApplication;
class GameState
{
private:
	using DelayedCallback = std::function<void()>;
	std::list<GameObject*> gameObjects;
	std::list<EventHandler*> eventHandlers;
	std::list<DelayedCallback> delayedCallbacks;
protected:
	SDLApplication* game;
public:
	void render() const;
	void update();
	void handleEvent(const SDL_Event&);

	GameState(SDLApplication* g);
	void addEventListener(EventHandler*);
	void addObject(GameObject*);
};
