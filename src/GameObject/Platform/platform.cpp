#include "platform.h"

platform::platform(double x, double y, double width, double height) 
	: gameObject(x, y, width, height)
{

}

// Constructor theo dia chi map 
platform::platform(int m, int n, std::string type) {
	setX(m * TILE_SIZE);
	setY(n * TILE_SIZE);
	setWidth(TILE_SIZE);
	setHeight(TILE_SIZE);
	setType(type);
}

std::string platform::platform::getType() {
	return type;
}

void platform::setType(std::string t) {
	this->type = t;
}

void platform::render(SDL_Renderer *renderer) {
	SDL_RenderTexture(renderer, getTexture(), nullptr, getRect());
}

void platform::update(float deltaTime) {

}