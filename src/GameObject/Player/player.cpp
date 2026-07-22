#include "player.h"

player::player(double x, double y, double width, double height)
    : gameObject(x, y, width, height)
{
    this->velocityX = 0.0;
    this->velocityY = 0.0;
    this->speed = 300.0;
    this->direction = 1;
    this->gravity = 980.0;
    this->jumpForce = 450.0;
    this->onGround = false;
    setTexture(nullptr);
}
player::player(double x, double y) {

    this->velocityX = 0.0;
    this->velocityY = 0.0;
    this->speed = 300.0;
    this->direction = 1;
    this->gravity = 980.0;
    this->jumpForce = 450.0;
    this->onGround = false;
    setTexture(nullptr);
}

player::player() : player(0.0, 0.0, 32.0, 32.0) {}

void player::update(float deltaTime) {

    velocityX = 0.0;
    if (isMovingLeft)  velocityX -= speed;
    if (isMovingRight) velocityX += speed;

    if (!onGround) {
        velocityY += gravity * deltaTime;
    }
    else {
        if (velocityY > 0) velocityY = 0.0;
    }

    setX(getX() + velocityX * deltaTime);
    setY(getY() + velocityY * deltaTime);

}

void player::render(SDL_Renderer* renderer) {
    if (renderer == nullptr) return;

    SDL_Texture* tex = getTexture();
    SDL_FRect* pRect = getRect();

    if (tex != nullptr) {
        SDL_RenderTexture(renderer, getTexture(), nullptr, getRect());
    }
    else {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, pRect);
    }
}

// Getters & Setters
int player::getDirection() { return direction; }
void player::setDirection(int d) { if (d != 0) direction = (d > 0) ? 1 : -1; }
void player::setSpeed(double speed) { this->speed = speed; }
void player::setOnGround(bool grounded) { this->onGround = grounded; }
bool player::isOnGround() const { return onGround; }
void player::setMovingLeft(bool left) {
    isMovingLeft = left;
    //isMovingRight = !left;
}
void player::setMovingRight(bool right) {
    isMovingRight = right;
    //isMovingLeft = !right;
}
void player::setVelocityX(double x) {
    velocityX = x;
}
void player::setVelocityY(double y) {
    velocityY = y;
}

double player::getJumpForce() {
    return jumpForce;
}