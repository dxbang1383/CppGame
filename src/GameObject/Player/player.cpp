#include "player.h"
#include<cmath>

player::player(double x, double y, double width, double height)
    : gameObject(x, y, width, height){
    setTexture(nullptr);
}
player::player(double x, double y) : gameObject(x, y, 48.0, 48.0) {
    setTexture(nullptr);
}

player::player() : player(0.0, 0.0, 48.0, 48.0) {}

void player::update(float deltaTime) {

    updateVelocityX(deltaTime);
    setX(getX() + velocityX * deltaTime);

    updateVelocityY(deltaTime);
    setY(getY() + velocityY * deltaTime);

    //std::cout << isOnGround() << " " << std::endl;
    //std::cout << IsTouchingLadder() << " " << getIsClimbing() << std::endl;

    updateState();
    updateAnimation(deltaTime);
}

void player::updateState() {
    // chi doi con tro, moi Animation tu giu nhip frame cua no
    if (!onGround)              current = &jumpAnim;
    else if (velocityX == 0.0)  current = &idleAnim;
    else                        current = &runAnim;
}

void player::updateAnimation(float deltaTime) {
    current->update(deltaTime);
}

void player::updateVelocityX(float deltaTime) {
    velocityX = 0.0;
    if (isMovingLeft) {
        velocityX = -speed;
    }
    if (isMovingRight) {
        velocityX += speed;
    }
}

void player::updateVelocityY(float deltaTime) {
    // update theo phương y 
    if (getIsClimbing() || isOnGround()) {
        // nếu đang trèo hoặc trên mặt đất thì không bị ảnh hưởng trọng lực 
        if (isOnGround()) {
            setVelocityY(0.0f);
        }
        // nếu trên thang thì ảnh hưởng bởi input ng chơi
        else {
            velocityY = 0;
            if (isMovingUp) setVelocityY(velocityY + -abs(climbSpeed));
            if (isMovingDown) setVelocityY(velocityY + abs(climbSpeed));
        }
    }
    else {
        setVelocityY(velocityY + gravity * deltaTime);
    }
}

void player::render(SDL_Renderer* renderer) {
    if (renderer == nullptr) return;

    SDL_Texture* tex = current->getTexture();
    SDL_FRect* pRect = getRenderRect();

    if (tex != nullptr) {
        SDL_FRect srcRect = current->getSrcRect();
        if (getDirection() == 1) {
            SDL_RenderTextureRotated(renderer, tex, &srcRect, pRect, 0.0, nullptr, SDL_FLIP_HORIZONTAL);
        }
        else {
            SDL_RenderTexture(renderer, tex, &srcRect, pRect);
        }
    }
    else {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, pRect);
    }
}  