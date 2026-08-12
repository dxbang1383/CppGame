#include "resourceManager.h"

// default 
std::map<std::string, std::string> resourceManager::pathTable = {
	{ "bkg",     "assets/kenney_pixel-platformer/bkg.png" },
	{ "P",       "assets/kenney_pixel-platformer/Tiles/tile_0002.png" },
	{ "player",  "assets/kenney_pixel-platformer/Tiles/Characters/tile_0000.png" },
	{ "map1",    "assets/kenney_pixel-platformer/Tilemap/tilemap_packed.png" },
	{ "enemy",   "assets/kenney_pixel-platformer/Tiles/Characters/tile_0024.png" },
	{ "player_idle", "assets/kenney_pixel-platformer/Tiles/Characters/tile_idle1.png" },
	{ "player_run",  "assets/kenney_pixel-platformer/Tiles/Characters/tile_run.png" },
	{ "player_jump", "assets/kenney_pixel-platformer/Tiles/Characters/tile_0001.png" },
	{ "ladder",      "assets/kenney_pixel-platformer/Tiles/tile_0071.png" },
};

std::map<std::string, SDL_Texture*> resourceManager::cache;

/*
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
	}
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

	if (s == "map1") {
		path = "assets/kenney_pixel-platformer/Tilemap/tilemap_packed.png";
	}

	SDL_Texture* texture = IMG_LoadTexture(renderer, path.c_str());
	if (!texture) {
		SDL_Log("Load anh Thatbai: %s", SDL_GetError());
	}
	SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);

	return texture;
}
*/

SDL_Texture* resourceManager::getTexture(SDL_Renderer* renderer, const std::string& key) {
	// check trong cache co chua neu co return luon 
	auto c = cache.find(key);
	if (c != cache.end()) return c->second;

	// kiem tra xem key co bind den path nao khong 
	auto p = pathTable.find(key);
	if (p == pathTable.end()) {
		SDL_Log("Khong co tai nguyen ten: %s", key.c_str());
		return nullptr;
	}

	// neu co bind den ma chua load thi load 1 lan roi luu trong cache 
	SDL_Texture* tex = IMG_LoadTexture(renderer, p->second.c_str());

	if (!tex) {
		SDL_Log("Load that bai %s: %s", p->second.c_str(), SDL_GetError());
		return nullptr;
	} 

	SDL_SetTextureScaleMode(tex, SDL_SCALEMODE_NEAREST);
	// them vao cache
	cache[key] = tex;
	return tex;
}

void resourceManager::clearAll() {
	for (auto& [key, tex] : cache)
		SDL_DestroyTexture(tex);
	cache.clear();
}