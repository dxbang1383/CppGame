#include "player.h"

// constructor
player::player(double x, double y, double width, double height)
    : gameObject(x, y, width, height)
{

}

// Constructor default
player::player() : gameObject(0, 0, 0, 0) {

}

void player::setSpeed(double speed) {
    this->speed = speed;
}

void player::setDirection(int d) {
    if (d < 0) this->direction = -1;
    else if (d == 0) this->direction = 0;
    else this->direction = 1;
}

void player::render(SDL_Renderer* renderer) {

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, getRect());
}

void player::update(float deltaTime) {
    setX(getX() + deltaTime * speed * direction);
    setY(getY() + deltaTime * gravity);
}
