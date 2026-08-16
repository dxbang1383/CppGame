#include "switch.h"

Switch::Switch(float x, float y, float w, float h, SDL_Texture* tex)
	: gameObject(x, y, w, h) {
	renderRect = { x, y, w, h };
	if (tex) setTexture(tex);
}

void Switch::setTexture(SDL_Texture* tex) {
	texture = tex;
	if (texture) {
		float texW = 0,		texH = 0;
		SDL_GetTextureSize(texture, &texW, &texH);
		frameWidth = texW / 2.0f;

		srcRect = { 0.0f, 0.0f, frameWidth, texH };
	}
}

void Switch::trigger() {
	if (!isActivated) {
		isActivated = true;
		srcRect.x = frameWidth;
	}
}

void Switch::updRenderRect(const SDL_FRect& cam) {
	renderRect.x = getX() - cam.x;
	renderRect.y = getY() - cam.y;
	renderRect.w = getWidth();
	renderRect.h = getHeight();
}

void Switch::render(SDL_Renderer* renderer) {
	if (texture) {
		SDL_RenderTexture(renderer, texture, &srcRect, &renderRect);
	}
}
