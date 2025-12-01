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
	using Anchor = std::list<GameObject*>::iterator;
	void render() const;
	void update();
	void handleEvent(const SDL_Event&);
	SDLApplication* getGame() const;
	Anchor addObject(GameObject*);
	void removeObject(Anchor);
	void runLater(DelayedCallback);

	GameState(SDLApplication* g);
	void addEventListener(EventHandler*);
};
