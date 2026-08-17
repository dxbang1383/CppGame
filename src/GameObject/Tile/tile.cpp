#include "tile.h"

tile::tile(double x, double y, double width, double height)
	: gameObject(x, y, width, height)
{
}

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
	if (srcRect.w == 0 || srcRect.h == 0) {
		// khong khai bao vung cat 
		SDL_RenderTexture(renderer, getTexture(), nullptr, getRenderRect());
	}
	else {
		SDL_RenderTexture(renderer, getTexture(), &srcRect, getRenderRect());
	}
}
