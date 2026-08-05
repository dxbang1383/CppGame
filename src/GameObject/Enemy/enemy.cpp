#include "enemy.h"

enemy::enemy(double x, double y, double width, double height)
	: gameObject(x, y, width, height) {
	speed = 120.0;
	direction = 1;
	velocityX = 0.0;
	minX = x - 150.0;
	maxX = x + 150.0;
}

enemy::enemy() : gameObject() {
	speed = 120.0;
	direction = 1;
	velocityX = 0.0;
	minX = 0.0;
	maxX = 0.0;
}

void enemy::update(float deltaTime) {
	velocityX = speed * direction;
	setX(getX() + velocityX * deltaTime);

	if (getX() < minX) { setX(minX); direction = 1; }
	else if (getX() > maxX) { setX(maxX); direction = -1; }

}

void enemy::render(SDL_Renderer* renderer) {
	if (getTexture() != nullptr)
		SDL_RenderTexture(renderer, getTexture(), nullptr, getRenderRect());
	else {
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(renderer, getRenderRect());
	}
}