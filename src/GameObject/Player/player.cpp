#include "player.h"

// constructor
player::player(double x, double y, double width, double height)
    : gameObject(x, y, width, height)
{

}

void player::setSpeed(double speed) {
    this->speed = speed;
}

void player::render(SDL_Renderer* renderer) {
    SDL_FRect rect = {
        player::getX(),
        player::getY(),
        player::getWidth(),
        player::getHeight()};

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void player::update(float deltaTime) {
    
}
