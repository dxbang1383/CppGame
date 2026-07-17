#include "platform.h"

platform::platform(double x, double y, double width, double height) 
	: gameObject(x, y, width, height)
{

}

void platform::render(SDL_Renderer *renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, getRect());
}

void platform::update(float deltaTime) {

}