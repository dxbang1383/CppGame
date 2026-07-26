#include "platform.h"

platform::platform(double x, double y, double width, double height) 
	: gameObject(x, y, width, height)
{

}

// Constructor theo dia chi map 
platform::platform(int m, int n, std::string type) {\
	// Set hình chữ nhật để in 
	setX(m * TILE_SIZE);
	setY(n * TILE_SIZE);
	setWidth(TILE_SIZE);
	setHeight(TILE_SIZE);
	// 
	setType(type);
}

platform::platform(int m, int n, std::string type, int srcX, int srcY) {
	// hình chữ nhật là địa chỉ trên scene 
	setX(m * TILE_SIZE);
	setY(n * TILE_SIZE);
	setWidth(TILE_SIZE);
	setHeight(TILE_SIZE);

	// hình chữ nhật địa chỉ hình vẽ trên sheet 
	srcRect = { srcX * TILE_MAP, srcY * TILE_MAP, TILE_MAP, TILE_MAP };

	setType(type);
}

std::string platform::platform::getType() {
	return type;
}

void platform::setType(std::string t) {
	this->type = t;
}

void platform::render(SDL_Renderer *renderer) {
	if (srcRect.w == 0 || srcRect.h == 0) 
	{
		SDL_RenderTexture(renderer, getTexture(), nullptr, getRect());
	}
	else 
	{
		SDL_RenderTexture(renderer, getTexture(), &srcRect, getRect());
	}
}

void platform::update(float deltaTime) {

}