#include "gameState.h"
#include "GameObject.h"
#include "EventHandler.h"
#include "SDLApplication.h"


GameState::GameState(SDLApplication* game)
	: game(game)
{
}

SDLApplication* GameState::getGame() const {
	return game;
}

void GameState::render() const {
	for (auto obj : gameObjects)
		obj->Render();
}

void GameState::update() {
	for (auto obj : gameObjects) {
		obj->Update();
	}

	for (auto& callback : delayedCallbacks) {
		callback();
	}
	delayedCallbacks.clear();
}

void GameState::handleEvent(const SDL_Event& e) {
	for (EventHandler* eh : eventHandlers) {
		eh->handleEvent(e);
	}
}

void GameState::addEventListener(EventHandler* event) {
	eventHandlers.push_back(event);
}

GameState::Anchor GameState::addObject(GameObject* object) {
	gameObjects.push_back(object);
	return --gameObjects.end();
}

void GameState::removeObject(Anchor it) {
	gameObjects.erase(it);
}

void GameState::runLater(DelayedCallback callback) {
	delayedCallbacks.push_back(callback);
}
