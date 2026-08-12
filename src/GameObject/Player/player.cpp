#include "player.h"
#include<cmath>

player::player(double x, double y, double width, double height)
    : gameObject(x, y, width, height)
{
    this->velocityX = 50.0;
    this->velocityY = 100.0;
    this->speed = 300.0;
    this->direction = 1;
    this->gravity = 980.0;
    this->jumpForce = 450.0;
    this->onGround = false;
    this->currentFrame = 0;
    this->totalFrame = 2;
    this->frameTime = 1.0f;
    this->frameTimer = 0.0f;
    this->frameWidth = 24;
    this->frameHeight = 24;
    this->aniRow = 0;
    this->currentState = PlayerState::STATE_IDLE;
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
    this->currentFrame = 0;
    this->totalFrame = 2;
    this->frameTime = 1.0f;
    this->frameTimer = 0.0f;
    this->frameWidth = 24;
    this->frameHeight = 24;
    this->aniRow = 0;
    this->currentState = PlayerState::STATE_IDLE;
    setTexture(nullptr);
}

player::player() : player(0.0, 0.0, 32.0, 32.0) {}

void player::update(float deltaTime) {

   
    velocityX = 0.0;
    if (isMovingLeft) {
        velocityX -= speed;
        direction = 1; 
    }
    if (isMovingRight) {
        velocityX += speed;
        direction = -1;  
    }
    if (!isTouchingLadder) {
        isClimbing = false;
    }

    if (isClimbing) {
        velocityY = 0.0;

        if (isMovingUp) {
            velocityY = -climbSpeed;
        }
        else if (isMovingDown) {
            velocityY = climbSpeed;
        }

        setX(getX() + velocityX * deltaTime);
        setY(getY() + velocityY * deltaTime);

        if (velocityX != 0 || velocityY != 0) {

        }
        return;
    }

    //Áp dụng Trọng lực trước khi xét State
    if (!onGround) {
        velocityY += gravity * deltaTime;
    }
    else {
        if (velocityY > 0) velocityY = 0.0;
    }

    //Cập nhật vị trí
    setX(getX() + velocityX * deltaTime);
    setY(getY() + velocityY * deltaTime);

    
    if (!onGround && abs(velocityY) > 1.0) {
        if (currentState != PlayerState::STATE_JUMP) {
            currentState = PlayerState::STATE_JUMP;
            setTexture(jumpTexture);
            totalFrame = 1;
            currentFrame = 0;
            frameTimer = 0.0f;
            frameTime = 0.1f;
        }
    }
    else {
        if (velocityX == 0.0) {
            if (currentState != PlayerState::STATE_IDLE) {
                currentState = PlayerState::STATE_IDLE;
                setTexture(idleTexture);
                totalFrame = 2;
                currentFrame = 0;
                frameTimer = 0.0f;
                frameTime = 0.1f;
            }
        }
        else {
            if (currentState != PlayerState::STATE_RUN) {
                currentState = PlayerState::STATE_RUN;
                setTexture(runTexture);
                totalFrame = 2;
                currentFrame = 0;
                frameTimer = 0.0f;
                frameTime = 0.05f;
            }
        }
    }

    //Cập nhật animation Frame 
    frameTimer += deltaTime;
    if (frameTimer >= frameTime) {
        frameTimer -= frameTime;
        currentFrame++;
        if (currentFrame >= totalFrame) {
            currentFrame = 0;
        }
    }
 }

void player::render(SDL_Renderer* renderer) {
    if (renderer == nullptr) return;

    SDL_Texture* tex = getTexture();
    SDL_FRect* pRect = getRect();

    if (tex != nullptr) {
        SDL_FRect srcRect = {
            (float)(currentFrame * frameWidth),
            (float)(aniRow * frameHeight),
            (float)(frameWidth),
            (float)(frameHeight)
        };
        if (getDirection() == -1) {
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
double player::getVelocityX() {
    return velocityX;
}

double player::getVelocityY() {
    return velocityY;
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