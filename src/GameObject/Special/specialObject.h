#ifndef SPECIAL_OBJECT_H
#define SPECIAL_OBJECT_H

#include <SDL3/SDL.h>
#include <string>
#include <cmath>
#include "../gameObject.h"

class specialObject : public gameObject {
private:
	SDL_FRect srcRect = { 0.0f, 0.0f, 0.0f, 0.0f }; // vung cat tren sheet

public:
	static constexpr float TILE_SIZE = 36; // kich thuoc 1 o trong THE GIOI

	specialObject(double x, double y, double width, double height)
		: gameObject(x, y, width, height) {
	}

	// Constructor theo dia chi o tren map
	specialObject(int col, int row) {
		setX(col * TILE_SIZE);
		setY(row * TILE_SIZE);
		setWidth(TILE_SIZE);
		setHeight(TILE_SIZE);
	}

	void setSrcRect(SDL_FRect rect) { srcRect = rect; }
	SDL_FRect getSrcRect() const { return srcRect; }

	int getCol() { return floor(getX()) / TILE_SIZE; }
	int getRow() { return floor(getY()) / TILE_SIZE; }

	void render(SDL_Renderer* renderer) override {
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
};

#endif // !SPECIAL_OBJECT_H
