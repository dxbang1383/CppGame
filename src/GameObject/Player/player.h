#ifndef PLAYER_H
#define PLAYER_H

#include <SDL3/SDL.h>
#include <iostream>
#include "../src/GameObject/gameObject.h"
#include "../src/engine/Animation.h"
#include "../src/gameObject/Special/Item.h"

class player : public gameObject {
private:
    const int playerSize = 48; // kich cỡ nhân vật
    double velocityX = 0.0; // vận tốc theo trục x 
    double velocityY = 0.0; // vận tốc theo trục y 
    double speed = 300.0; // tốc độ của nhân vật
    int direction = 1; // hướng của nhân vật 
    double gravity = 980.0; // tốc độ của trọng lực
    double jumpForce = 450.0; // tốc độ nhảy 
    bool onGround = false; // trêm mặt đất hay không 
    //Item
    bool hasDoubleJump = false;
    bool doubleJumpUsed = false;
    bool noGravity = false;

    bool highJump = false;
    bool speedBoost = false;
    bool starPower = false;
    
    int coins = 0;
    int health = 3;

    double normalJumpForce = 450.0;
    double normalSpeed = 450.0;
    //TimerItem
    double starTimer = 0.0;
    double noGravityTimer = 0.0;
    double highJumpTimer = 0.0;
    double speedTimer = 0.0;

    // Luu sheet dang lam
    SDL_Texture* idleTexture = nullptr; 
    SDL_Texture* runTexture = nullptr;
    SDL_Texture* jumpTexture = nullptr;
    //Trang thai xu li frame cho nhan vat
    PlayerState currentState; // lựa chọn các trạng thái trong enum để chạy animation
    int currentFrame;
    int totalFrame;
    float frameTime;
    float frameTimer;

    float frameWidth;
    float frameHeight;
    int aniRow;
    double jumpForce = 600.0; // tốc độ nhảy 
    bool onGround = false; // trêm mặt đất hay không
    // Animation cho tung trang thai, moi cai giu nhip frame rieng
    Animation idleAnim{ 2, 0.10f };
    Animation runAnim { 2, 0.05f };
    Animation jumpAnim{ 1, 0.10f };
    // Animation dang duoc chay, luon tro toi 1 cai hop le
    Animation* current = &idleAnim;
    // Trạng thái nút bấm
    bool isMovingLeft = false;
    bool isMovingRight = false;
    bool isMovingUp = false;
    bool isMovingDown = false;

    // Trạng thái cầu thang
    bool isClimbing = false;
    bool isTouchingLadder = false;
    float climbSpeed = 300.0f;

public:
    // Constructor
    player(double x, double y, double width, double height);
    player(double x, double y);
    player();

    // Getters & Setters
    int getDirection() { return direction; }
    void setSpeed(double speed) { this->speed = speed; }
    void setDirection(int d) { if (d != 0) direction = (d > 0) ? 1 : -1; }
    bool isOnGround() const { return onGround; }
    void setMovingLeft(bool left) { isMovingLeft = left; }
    void setMovingRight(bool right) { isMovingRight = right; }
    void setMovingUp(bool up) { isMovingUp = up; }
    void setMovingDown(bool down) { isMovingDown = down; }
    void setVelocityX(double x) { velocityX = x; }
    void setVelocityY(double y) { velocityY = y; }
    double getVelocityX() const { return velocityX; }
    double getVelocityY() const { return velocityY; }
    double getJumpForce() { return jumpForce; }
    void setOnGround(bool grounded) {
        this->onGround = grounded;
        if (grounded) {
            doubleJumpUsed = false;
        }
    }
    // Ham sceneMain nap anh vao cho player
    void setIdleTexture(SDL_Texture* tex) { idleAnim.setTexture(tex); }
    void setRunTexture(SDL_Texture* tex) { runAnim.setTexture(tex); }
    void setJumpTexture(SDL_Texture* tex) { jumpAnim.setTexture(tex); }
    void setIsTouchingLadder(bool touch) { isTouchingLadder = touch; }
    bool IsTouchingLadder() const { return this->isTouchingLadder; }
    bool getIsClimbing() { return isClimbing; }
    void setIsClimbing(bool climbing) { isClimbing = climbing; }

    void updateState();
    // hàm này chỉ cập nhật hcn vị trí in ảnh 
    void updateAnimation(float deltaTime);
    void updateVelocityX(float deltaTime);
    void updateVelocityY(float deltaTime);

    // Di chuyen theo tung truc, dung cho va cham tach truc trong sceneMain
    void moveX(float deltaTime) { setX(getX() + velocityX * deltaTime); }
    void moveY(float deltaTime) { setY(getY() + velocityY * deltaTime); }
    
    void render(SDL_Renderer* renderer) override;
    void update(float deltaTime) override;
    //Item
    bool isNoGravity() const { return noGravity; }
    void collectItem(ItemType type);
    void updateItemEffects();
    void updateItem(float deltaTime);
    void isInvincible() const;
    void canDoubleJump() const;
    bool hasNoGravity() const;
    bool hasHighJump() const;
    bool hasSpeedBoost() const;
    int getCoins() const;
    int getHealth() const;
    void jump();
};

#endif // !PLAYER_H