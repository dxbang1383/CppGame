#ifndef SPIKE_H
#define SPIKE_H

#include <SDL3/SDL.h>
#include <string>
#include "tile.h"

/*
	Bay chong tren luoi o. Cham vao la thua.
	Ke thua tile nen dung san texture / renderRect / updRenderRect(camera).
	Chi ghi de render() de bay dang tat thi khong ve.
*/
class spike : public tile {
private:
	bool active = true;

public:
	spike(int col, int row, std::string texKey = "spike")
		: tile(col, row, texKey) {
	}

	bool isActive() const { return active; }
	void setActive(bool status) { active = status; }

	void render(SDL_Renderer* renderer) override {
		if (!active) return;
		tile::render(renderer);
	}
};

#endif // !SPIKE_H
