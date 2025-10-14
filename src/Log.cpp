#include "Log.h"

Log::Log(Vector2D<float> sentido, Point2D<float> posicion, Texture* textura, Game* juego) :
	speed(sentido),
	position(posicion),
	texture(textura),
	game(juego)
{

}

void Log::Render() const {
	SDL_FRect hitbox = { (float)position.GetX(), (float)position.GetY(),
				(float)texture->getFrameWidth(), (float)texture->getFrameHeight() };
	texture->renderFrame(hitbox, 0, 0);
}

void Log::Update() {
	position = position + speed * (game->FRAME_RATE / 1000.0);
	if (position.GetX() < -150) position = { position.GetX() + 150 + game->WINDOW_WIDTH , position.GetY() };
	else if (position.GetX() > game->WINDOW_WIDTH) position = { position.GetX() - 150 - game->WINDOW_WIDTH, position.GetY() };
}
