#include "decor.h"

// anim giu nguyen mac dinh (frameCount = 1) nen hasAnim() tra false
decor::decor(int col, int row, std::string texKey, int srcX, int srcY)
	: tile(col, row, texKey, srcX, srcY)
{
}

// texKey = ten sprite trong Animation, srcRect de trong
decor::decor(int col, int row, std::string animKey)
	: tile(col, row, animKey),
	  anim(ANIM_FRAMES, ANIM_TIME)
{
	typeFrame = typeAni;
	animationEnable = true;
}

void decor::update(float deltaTime) {
	anim.update(deltaTime);
}

// ve o red neu khong co texture
void decor::render(SDL_Renderer* renderer) {
	if (!hasAnim()) {
		tile::render(renderer);
		return;
	}

	SDL_Texture* tex = anim.getTexture();
	if (tex == nullptr) {
		// in o RED neu loi
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(renderer, getRenderRect());
		return;
	}

	SDL_FRect src = anim.getSrcRect();
	SDL_RenderTexture(renderer, tex, &src, getRenderRect());
}
