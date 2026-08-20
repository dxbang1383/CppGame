#include "fish.h"

fish::fish(int col, int row, int patrol) : enemy(col, row, patrol) {
	type = "fish";
	anim = Animation(2, 0.2f);

	patrolMinY = getY() - 3 * tile::TILE_SIZE;
	patrolMaxY = getY() + 3 * tile::TILE_SIZE;
	direction = -1;
}

void fish::update(float deltaTime) {
	if (!alive) return;

	velocityY = speed * direction;
	setY(getY() + velocityY * deltaTime);

	if (getY() < patrolMinY) { setY(patrolMinY); direction = 1; }
	else if (getY() > patrolMaxY) { setY(patrolMaxY); direction = -1; }

	anim.update(deltaTime);
}

void fish::render(SDL_Renderer* renderer) {
	if (!alive) return;

	SDL_Texture* tex = anim.getTexture();
	SDL_FRect* pRect = getRenderRect();

	if (tex != nullptr) {
		SDL_FRect srcRect = anim.getSrcRect();
		if (direction == 1) {
			SDL_RenderTextureRotated(renderer, tex, &srcRect, pRect,
				0.0, nullptr, SDL_FLIP_VERTICAL);
		}
		else {
			SDL_RenderTexture(renderer, tex, &srcRect, pRect);
		}
	}
	else {
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(renderer, pRect);
	}
}
