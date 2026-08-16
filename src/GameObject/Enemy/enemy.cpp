#include "enemy.h"

enemy::enemy(int col, int row, int patrol)
	: gameObject(col * platform::TILE_SIZE, row * platform::TILE_SIZE,
		platform::TILE_SIZE, platform::TILE_SIZE) {
	this->patrol = patrol;
}

void enemy::render(SDL_Renderer* renderer) {

	if (renderer == nullptr) {
		std::cout << "renderer chua duoc nap vao (enemy)" << std::endl;
	}
	// neu chet thi thoi 
	if (!alive) return;

	// logic render
	SDL_Texture* tex = anim.getTexture();
	SDL_FRect* pRect = getRenderRect();

	if (tex != nullptr) {
		SDL_FRect srcRect = anim.getSrcRect();
		if (direction == 1) {
			SDL_RenderTextureRotated(renderer, tex, &srcRect, pRect,
				0.0, nullptr, SDL_FLIP_HORIZONTAL);
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
