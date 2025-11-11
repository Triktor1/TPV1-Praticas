#include "Log.h"

void Log::Render() const {
	SDL_FRect hitbox = { (float)position.GetX(), (float)position.GetY(),
				(float)texture->getFrameWidth(), (float)texture->getFrameHeight() };
	texture->renderFrame(hitbox, 0, 0);
}

void Log::Update() {
	position = position + speed * (game->FRAME_RATE / 1000.0);
	if (position.GetX() >= game->WINDOW_WIDTH + 150 - texture->getFrameWidth()) position = { position.GetX() - 150*2 - game->WINDOW_WIDTH, position.GetY()};
}

Collision Log::CheckCollision(const SDL_FRect& FRect) {
	Collision collision;
	SDL_FRect col{ position.GetX(), position.GetY(), (float)texture->getFrameWidth(), (float)texture->getFrameHeight() };
	if (SDL_HasRectIntersectionFloat(&FRect, &col)) {
		collision.tipo = PLATFORM;
		collision.speed = speed;
	}
	else collision.tipo = NONE;

	return collision;
}
