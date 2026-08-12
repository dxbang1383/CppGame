#include "resourceManager.h"

SDL_Texture* resourceManager::loadImage(SDL_Renderer* renderer, std::string s) {
	std::string path = "def";

	if (s == "default") {
		path = "assets/kenney_pixel-platformer/bkg.png";
	}
	else if (s == "P") {
		path = "assets/kenney_pixel-platformer/Tiles/tile_0002.png";
	}
	/*else if (s == "player") {
		path = "assets/kenney_pixel-platformer/Tiles/Characters/tile_run.png";
	}*/
	else if (s == "player_idle") {
		path = "assets/kenney_pixel-platformer/Tiles/Characters/tile_idle1.png";
	}
	else if (s == "player_run") {
		path = "assets/kenney_pixel-platformer/Tiles/Characters/tile_run.png";
	}
	else if (s == "player_jump") {
		path = "assets/kenney_pixel-platformer/Tiles/Characters/tile_0001.png";
	}
	else if (s == "ladder") {
		path = "assets/kenney_pixel-platformer/Tiles/tile_0071.png";
	}
	SDL_Texture* texture = IMG_LoadTexture(renderer, path.c_str());
	if (!texture) {
		SDL_Log("Load anh Thatbai: %s", SDL_GetError());
	}
	SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);

	return texture;
}