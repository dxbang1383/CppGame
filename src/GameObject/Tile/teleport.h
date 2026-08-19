#ifndef TELEPORT_H
#define TELEPORT_H

#include <SDL3/SDL.h>
#include <string>
#include "tile.h"
#include "../../engine/UI/Text.h"

class teleport : public tile {
private:
	int groupId = 0;

public:
	teleport(int col, int row, int groupId)
		: tile(col, row, "teleport"), groupId(groupId) {
	}

	int getGroupId() const { return groupId; }

	void render(SDL_Renderer* renderer) override {
		SDL_FRect* r = getRenderRect();

		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

		// nền 
		SDL_SetRenderDrawColor(renderer, 80, 220, 120, 90);
		SDL_RenderFillRect(renderer, r);

		// viền 
		SDL_SetRenderDrawColor(renderer, 40, 180, 90, 255);
		SDL_RenderRect(renderer, r);

		// in số nhóm 
		SDL_Color white = { 255, 255, 255, 255 };
		Text::draw(renderer, std::to_string(groupId),
			r->x + 4.0f, r->y + 4.0f, white, 0.35f);
	}
};

#endif // !TELEPORT_H
