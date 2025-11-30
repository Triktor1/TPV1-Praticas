#include "gameState.h"
#include "GameObject.h"
#include "EventHandler.h"

void GameState::render() const {
	for (auto obj : gameObjects)
		obj->Render();
}

void GameState::update() {
	for (auto obj : gameObjects)
		obj->Update();
}

void GameState::handleEvent(const SDL_Event& e) {
	
}
