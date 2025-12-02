#include "Wasp.h"
#include "PlayState.h"
#include "SDLApplication.h"

Wasp::Wasp(Point2D<float> position, Vector2D<float> speed, Texture* texture, PlayState* game, float lifeTime) :
	SceneObject(position, texture, game),
	speed(speed),
	lifeTime(lifeTime),
	anchorGS(),
	anchorPS()
{
	this->game = game;
}

Wasp::Wasp(PlayState* game, std::istream& file) :
	SceneObject(game, file),
	anchorGS(),
	anchorPS()
{
	this->game = game;
	float posX, posY, speedX, speedY, time;
	file >> posX >> posY >> speedX >> speedY >> time;
	position = Vector2D<float>(posX, posY);
	speed = Vector2D<float>(speedX, speedY);
	lifeTime = time;
	texture = this->texture = game->getGame()->getTexture(game->getGame()->WASP);
}

void Wasp::Update() {
	position = position + speed * (game->getGame()->FRAME_RATE / 1000.0f);
	lifeTime -= game->getGame()->FRAME_RATE;
	if (!isAlive()) {
		game->runLater([this] {
			this->game->removeObject(anchorGS);
			this->game->removeSceneObject(anchorPS);
			delete this;
			});
		game->deleteAfter(anchorPS);
	}
}

Collision Wasp::checkCollision(const SDL_FRect& FRect) const {
	Collision collision;
	SDL_FRect col{ position.GetX(), position.GetY(), texture->getFrameWidth(), texture->getFrameHeight() };
	if (SDL_HasRectIntersectionFloat(&FRect, &col))
		collision.tipo = ENEMY;
	else collision.tipo = NONE;

	return collision;
}

bool Wasp::isAlive() const {
	return lifeTime >= 0;
}

int Wasp::getLifeTime() const {
	return lifeTime;
}
