#include "Palette.h"


Palette::Palette(float x, float y, std::string type) {

	this->x = x; this->y = y;
	this->width = 400; this->height = 270;

	// Khởi tạo hcn
	rect.x = this->x;
	rect.y = this->y;
	rect.h = this->height;
	rect.w = this->width;
	texRect = rect;

	srcX = -1;
	srcY = -1;

	this->type = type;
	this->tex = nullptr;
}

void Palette::setSize() {
	float w, h = 0;
	SDL_GetTextureSize(tex, &w, &h);
	this->width = w * 2;
	rect.w = this->width;
	texRect.w = this->width;

	this->height = h * 2;
	rect.h = this->height;
	texRect.h = this->height;
}

void Palette::renderGrid(SDL_Renderer* renderer) {

}

void Palette::render(SDL_Renderer* renderer) {
	SDL_RenderTexture(renderer, getTexture(), nullptr, getTexRect());
	if (gridState) {
		renderGrid(renderer);
	}
}

void Palette::update(float deltaTime) {
	setSize();
}

void Palette::mouseClick(int x, int y) {
	x = x - this->x;
	y = y - this->y;

	if (x < this->width && y < this->height) {
		srcX = x / 36;
		srcY = y / 36;
	}
}