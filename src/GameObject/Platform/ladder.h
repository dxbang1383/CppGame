#ifndef LADDER_H
#define LADDER_H

#include <SDL3/SDL.h>
#include <string>
#include "../src/GameObject/gameObject.h"

class ladder : public gameObject {
public:
	ladder(double x, double y, double width = 32.0, double height = 32.0)
		: gameObject(x, y, width, height) {}
	
	void render(SDL_Renderer* renderer) {
		SDL_Texture* tex = getTexture();
		SDL_FRect* pRect = getRect();
		if (tex != nullptr) {
			SDL_RenderTexture(renderer, tex, nullptr, pRect);
		}
	}
};

#endif