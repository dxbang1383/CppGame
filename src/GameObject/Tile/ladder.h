#ifndef LADDER_H
#define LADDER_H

#include <SDL3/SDL.h>
#include <string>
#include "../gameObject.h"

class ladder : public gameObject {
public:
	ladder(double x, double y, double width = 32.0, double height = 32.0)
		: gameObject(x, y, width, height) {}

	void render(SDL_Renderer* renderer) override {
		SDL_Texture* tex = getTexture();
		if (tex != nullptr) {
			SDL_RenderTexture(renderer, tex, nullptr, getRenderRect());
		}
	}
};

#endif
