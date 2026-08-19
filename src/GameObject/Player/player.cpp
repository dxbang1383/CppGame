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
    // Cập nhật đếm ngược thời gian của các hiệu ứng
    updateItem(deltaTime);

    updateVelocityX(deltaTime);
    setX(getX() + velocityX * deltaTime);

    updateVelocityY(deltaTime);
    setY(getY() + velocityY * deltaTime);

    //std::cout << isOnGround() << " " << std::endl;
    //std::cout << IsTouchingLadder() << " " << getIsClimbing() << std::endl;

    updateState();
    updateAnimation(deltaTime);

    if (hurtTimer > 0.0) {
        hurtTimer -= deltaTime;
        if (hurtTimer < 0.0) hurtTimer = 0.0;
    }
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
    // Vat pham NO_GRAVITY: bay tu do theo phim bam, khong chiu trong luc
    if (noGravity) {
        velocityY = 0.0;
        if (isMovingUp)   velocityY -= speed;
        if (isMovingDown) velocityY += speed;
        return;
    }

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

    // return để không in hình 10 lần 1 /s
    if (hurtTimer > 0.0 && ((int)(hurtTimer * 10) % 2) == 0) return;

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

void player::collectItem(ItemType type) {
    switch (type) {
        case ItemType::COIN1:
            coins++;
            break;
        case ItemType::STAR:
            starPower = true;
            starTimer = 10.0;
            break;
        case ItemType::DOUBLE_JUMP:
            hasDoubleJump = true;
            doubleJumpUsed = false;
            break;
        case ItemType::NO_GRAVITY:
            noGravity = true;
            noGravityTimer = 10.0;
            break;
        case ItemType::HIGH_JUMP:
            highJump = true;
            jumpForce = normalJumpForce * 2;
            highJumpTimer = 10.0;
            break;
        case ItemType::HEART:
            health++;
            if (health > 5) 
                health = 5;
            break;
        case ItemType::SPEED:
            speedBoost = true;
            speed = normalSpeed * 1.5;
            speedTimer = 10.0;
            break;
    }
}
void player::updateItem(float deltaTime) {
    if (starPower) {
        starTimer -= deltaTime;

        if (starTimer <= 0.0) {
            starPower = false;
            starTimer = 0.0;
        }
    }

    if (noGravity) {
        noGravityTimer -= deltaTime;
        if (noGravityTimer <= 0.0) {
            noGravity = false;
            noGravityTimer = 0.0;
        }
    }

    if (highJump) {
        highJumpTimer -= deltaTime;
        if (highJumpTimer <= 0) {
            highJump = false;
            highJumpTimer = 0.0;
            jumpForce = normalJumpForce;
        }
    }

    if (speedBoost) {
        speedTimer -= deltaTime;
        if (speedTimer <= 0.0) {
            speedBoost = false;
            speedTimer = 0.0;
            speed = normalSpeed;
        }
    }
}

void player::jump() {
    if (onGround) {
        velocityY = -jumpForce;
        onGround = false;
        doubleJumpUsed = false;
    } else if (hasDoubleJump && !doubleJumpUsed) {
        velocityY = -jumpForce * 0.9f;
        doubleJumpUsed = true;
    }
}




void player::reset() {
    velocityX = 0.0;
    velocityY = 0.0;
    direction = 1;
    onGround = false;

    hasDoubleJump = false;
    doubleJumpUsed = false;
    noGravity = false;
    highJump = false;
    speedBoost = false;
    starPower = false;

    coins = 0;
    health = 3;

    jumpForce = normalJumpForce;
    speed = normalSpeed;

    starTimer = 0.0;
    noGravityTimer = 0.0;
    highJumpTimer = 0.0;
    speedTimer = 0.0;

    isMovingLeft = false;
    isMovingRight = false;
    isMovingUp = false;
    isMovingDown = false;

    isClimbing = false;
    isTouchingLadder = false;

    current = &idleAnim;
}
