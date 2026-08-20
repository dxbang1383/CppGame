#include "tile.h"


// Constructor theo dia chi o tren map
tile::tile(int m, int n, std::string t) {
	setX(m * TILE_SIZE);
	setY(n * TILE_SIZE);
	setWidth(TILE_SIZE);
	setHeight(TILE_SIZE);

	setType(t);
}

// Khoi tao gan theo sprite sheet
tile::tile(int m, int n, std::string t, int srcX, int srcY) {
	// hinh chu nhat la dia chi tren scene
	setX(m * TILE_SIZE);
	setY(n * TILE_SIZE);
	setWidth(TILE_SIZE);
	setHeight(TILE_SIZE);

	// hinh chu nhat dia chi hinh ve tren sheet
	srcRect = { srcX * TILE_MAP, srcY * TILE_MAP, TILE_MAP, TILE_MAP };

	setType(t);
}

void tile::render(SDL_Renderer* renderer) {
	SDL_Texture* tex = getTexture();

	if (tex == nullptr) {
		// in o RED neu loi
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(renderer, getRenderRect());
		return;
	}

	if (srcRect.w == 0 || srcRect.h == 0) {
		SDL_RenderTexture(renderer, tex, nullptr, getRenderRect());
	}
	else {
		SDL_RenderTexture(renderer, tex, &srcRect, getRenderRect());
	}
}
