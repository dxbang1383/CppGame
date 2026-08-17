#include "decor.h"

decor::decor(int m, int n, std::string t, int srcX, int srcY, std::string key)
	: tile(m, n, t, srcX, srcY),
	  anim(ANIM_FRAMES, ANIM_TIME),
	  animKey(key)
{
}

void decor::update(float deltaTime) {
	// Animation tu thoat ngay neu frameCount <= 1 nen khong can kiem tra o day
	anim.update(deltaTime);
}

void decor::render(SDL_Renderer* renderer) {
	if (anim.getTexture() != nullptr) {
		SDL_FRect src = anim.getSrcRect();
		SDL_RenderTexture(renderer, anim.getTexture(), &src, getRenderRect());
	}
	else {
		// Chua nap duoc sprite -> ve hinh tinh cat tu sheet
		tile::render(renderer);
	}
}
