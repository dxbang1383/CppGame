#include "resourceManager.h"

// default 
std::map<std::string, std::string> resourceManager::pathTable = {
	{ "bkg",     "assets/kenney_pixel-platformer/bkg.png" },
	{ "P",       "assets/kenney_pixel-platformer/Tiles/tile_0002.png" },
	{ "player",  "assets/kenney_pixel-platformer/Tiles/Characters/tile_0000.png" },
	{ "map1",    "assets/kenney_pixel-platformer/Tilemap/tilemap_packed.png" },
	{ "map2",    "assets/kenney_pixel-platformer/Tilemap/tilemap_packed2.png" },
	{ "map3",    "assets/kenney_pixel-platformer/Tilemap/tilemap_packed3.png" },
	{ "map4",    "assets/kenney_pixel-platformer/Tilemap/tilemap_packed4.png" },
	{ "map5",    "assets/kenney_pixel-platformer/Tilemap/marble_packed.png" },
	{ "map6",    "assets/kenney_pixel-platformer/Tilemap/rock_packed.png" },
	{ "map7",    "assets/kenney_pixel-platformer/Tilemap/sand_packed.png" },
	{ "map8",    "assets/kenney_pixel-platformer/Tilemap/stone_packed.png" },
	{ "enemy",   "assets/kenney_pixel-platformer/Tiles/Characters/tile_0024.png" },

	{ "player_idle", "assets/kenney_pixel-platformer/Tiles/Characters/tile_idle1.png" },
	{ "player_run",  "assets/kenney_pixel-platformer/Tiles/Characters/tile_run.png" },
	{ "player_jump", "assets/kenney_pixel-platformer/Tiles/Characters/tile_0001.png" },

	{ "ladder",      "assets/kenney_pixel-platformer/Tiles/ladder_down.png" },
	{ "ladder_down", "assets/kenney_pixel-platformer/Tiles/ladder_down.png" },
	{ "ladder_top",  "assets/kenney_pixel-platformer/Tiles/ladder_top.png" },

	{ "flyer",       "assets/kenney_pixel-platformer/Tiles/Enemy/flyer.png" },
	{ "walker",      "assets/kenney_pixel-platformer/Tiles/Characters/tile_0024.png" },

	{ "walker1",     "assets/kenney_pixel-platformer/Tiles/Enemy/walker1.png" },
	{ "walker2",     "assets/kenney_pixel-platformer/Tiles/Enemy/walker2.png" },
	{ "walker3",     "assets/kenney_pixel-platformer/Tiles/Enemy/walker3.png" },

	{ "menu",        "assets/kenney_pixel-platformer/menu.png" },
	 
	{ "water",          "assets/kenney_pixel-platformer/Tiles/Animation/water.png" },
	{ "waterfall_top",  "assets/kenney_pixel-platformer/Tiles/Animation/waterfall_top.png" },
	{ "waterfall_mid",  "assets/kenney_pixel-platformer/Tiles/Animation/waterfall_mid.png" },
	{ "waterfall_bot",  "assets/kenney_pixel-platformer/Tiles/Animation/waterfall_bot.png" },
	{ "flag",           "assets/kenney_pixel-platformer/Tiles/Animation/flag.png" },
	{ "bkg",			"assets/kenney_pixel-platformer/bkg.png" },
	{ "P",				"assets/kenney_pixel-platformer/Tiles/tile_0002.png" },
	{ "player",			"assets/kenney_pixel-platformer/Tiles/Characters/tile_0000.png" },
	{ "map1",			"assets/kenney_pixel-platformer/Tilemap/tilemap_packed.png" },
	{ "enemy",			"assets/kenney_pixel-platformer/Tiles/Characters/tile_0024.png" },

	{ "player_idle",	"assets/kenney_pixel-platformer/Tiles/Characters/tile_idle1.png" },
	{ "player_run",		"assets/kenney_pixel-platformer/Tiles/Characters/tile_run.png" },
	{ "player_jump",	"assets/kenney_pixel-platformer/Tiles/Characters/tile_0001.png" },

	{ "ladder",			"assets/kenney_pixel-platformer/Tiles/tile_0071.png" },

	{ "switch",			"assets/kenney_pixel-platformer/Tiles/tile_switch.png" },

	{ "spike",			"assets/kenney_pixel-platformer/Tiles/tile_0068.png" },
	// box
	{ "box_coin",		"assets/kenney_pixel-platformer/Tiles/tile_coin.png" },
	{ "box_question",	"assets/kenney_pixel-platformer/Tiles/tile_question.png"},
	{ "box_item",		"assets/kenney_pixel-platformer/Tiles/tile_item.png" },
	// item 
	{ "i_coin",			"assets/kenney_pixel-platformer/Tiles/tile_coin1.png"},
	{ "i_heart",		"assets/kenney_pixel-platformer/Tiles/tile_heart.png"},
	{ "i_star",			"assets/kenney_pixel-platformer/Tiles/tile_star.png" },
	{ "i_highjump",		"assets/kenney_pixel-platformer/Tiles/tile_highjump.png" },
	{ "i_speed",		"assets/kenney_pixel-platformer/Tiles/tile_speed.png" },
	{ "i_doublejump",	"assets/kenney_pixel-platformer/Tiles/tile_doublejump.png" },
	{ "i_nogravity",	"assets/kenney_pixel-platformer/Tiles/tile_nogravity.png" }

};

std::map<std::string, SDL_Texture*> resourceManager::cache;

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