#pragma once
#include <list>
#include <functional> 

class GameObject;
class EventHandler;
class GameState
{
protected:
	using DelayedCallback = std::function<void()>;
	std::list<GameObject*> gameObjects;
	std::list<EventHandler*> eventHandlers;
	std::list<DelayedCallback> delayedCallbacks;
};

