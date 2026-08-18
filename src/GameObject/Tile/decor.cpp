#include "decor.h"

// Decor DONG: dung vung cat cua tile roi tu doi khung theo typeAni
decor::decor(int m, int n, std::string t, int srcX, int srcY, std::string typeAni)
	: tile(m, n, t, srcX, srcY)
{
	typeFrame = typeAni;
	animationEnable = true;
}

void decor::update(float deltaTime) {
	if (animationEnable == false) return;

	time = time + deltaTime;

	if (time >= timeFrame) {
		if (frame == 1) frame = 2;
		else frame = 1;
		time = 0.0f;
	}
}

void decor::render(SDL_Renderer* renderer) {
	// Dang TINH thi ve y het tile
	if (animationEnable == false) {
		tile::render(renderer);
		return;
	}

	SDL_Texture* tex = getTexture();

	if (tex == nullptr) {
		// in o RED neu loi
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(renderer, getRenderRect());
		return;
	}

	// Dung lai vung cat goc tu chi so o tren sheet
	SDL_FRect temp = { getSrcX() * TILE_MAP, getSrcY() * TILE_MAP, TILE_MAP, TILE_MAP };

	// frame == 1 thi giu khung goc, frame == 2 thi nhay sang khung ke tiep
	if (frame != 1) {
		if (typeFrame == "x++") {
			temp.x = temp.x + TILE_MAP;
		}
		else if (typeFrame == "y++") {
			temp.y = temp.y + TILE_MAP;
		}
	}

	SDL_RenderTexture(renderer, tex, &temp, getRenderRect());
}
