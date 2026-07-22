#include "resourceManager.h"

SDL_Texture* resourceManager::loadImage(SDL_Renderer* renderer, std::string s) {
	std::string path = "def";

	if (s == "default") {
		path = "assets/kenney_pixel-platformer/bkg.png";
	}
	if (s == "P") {
		path = "assets/kenney_pixel-platformer/Tiles/tile_0002.png";
	}
	if (s == "player") {
		path = "assets/kenney_pixel-platformer/Tiles/Characters/tile_0000.png";
	}

	SDL_Texture* texture = IMG_LoadTexture(renderer, path.c_str());
	if (!texture) {
		SDL_Log("Load anh Thatbai: %s", SDL_GetError());
	}
	SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);

	return texture;
}