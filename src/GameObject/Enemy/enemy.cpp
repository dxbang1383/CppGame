#include "enemy.h"

enemy::enemy(double x, double y, double width, double height) : gameObject(x, y, width, height) {

}

enemy::enemy() : gameObject() {
}

void enemy::update(float deltaTime) {

}

void enemy::render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, getRect());
}