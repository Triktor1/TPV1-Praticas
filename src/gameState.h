#pragma once
#include <list>
#include <functional> 

class GameObject;
class EventHandler;
class GameState
{
protected:
	using DelayedCallback = std::function<void()>;
	list<GameObject*> gameObjects;
	list<EventHandler*> eventHandlers;
	list<DelayedCallback> delayedCallbacks;
};

