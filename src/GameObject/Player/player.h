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
    double jumpForce = 600.0; // tốc độ nhảy 
    bool onGround = false; // trêm mặt đất hay không 
    // Item
    bool hasDoubleJump = false;
    bool doubleJumpUsed = false;
    bool noGravity = false;

    bool highJump = false;
    bool speedBoost = false;
    bool starPower = false;
    
    int coins = 0;
    int diamonds = 0;
    int health = 3;

    double normalJumpForce = 600.0;  // khop voi jumpForce o tren
    double normalSpeed = 300.0;      // khop voi speed o tren

    // TimerItem
    double starTimer = 0.0;
    double noGravityTimer = 0.0;
    double highJumpTimer = 0.0;
    double speedTimer = 0.0;

    // Mien thuong ngan sau khi trung don
    double hurtTimer = 0.0;
    static constexpr double HURT_TIME = 1.0;

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
    bool getIsMovingDown() const { return isMovingDown; }
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

    // Tru mau. Tra ve false neu dang mien thuong 
    bool takeDamage() {
        if (hurtTimer > 0.0 || starPower) return false;
        health = health - 1;
        hurtTimer = HURT_TIME;
        return true;
    }

    // Ham sceneMain nap anh vao cho player
    void setIdleTexture(SDL_Texture* tex) { idleAnim.setTexture(tex); }
    void setRunTexture(SDL_Texture* tex) { runAnim.setTexture(tex); }
    void setJumpTexture(SDL_Texture* tex) { jumpAnim.setTexture(tex); }
    void setIsTouchingLadder(bool touch) { isTouchingLadder = touch; }
    bool IsTouchingLadder() const { return this->isTouchingLadder; }
    bool getIsClimbing() { return isClimbing; }
    void setIsClimbing(bool climbing) { isClimbing = climbing; }
    void setHealth(int h = 3) { this->health = h; }
   
    void clearHurt() { hurtTimer = 0.0; }

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
    void collectItem(ItemType type);
    void updateItem(float deltaTime);
    void jump();

    bool isNoGravity()   const { return noGravity; }
    // vua trung don, dung de nhap nhay khi ve
    bool isHurt()        const { return hurtTimer > 0.0; }
    
    bool isInvincible()  const { return starPower || hurtTimer > 0.0; }
    bool hasHighJump()   const { return highJump; }
    bool hasSpeedBoost() const { return speedBoost; }
    bool canDoubleJump() const { return hasDoubleJump && !doubleJumpUsed; }
    void addCoins(int val) { coins += val; }
    void addDiamond(int val = 1) { diamonds += val; }
    int  getCoins()      const { return coins; }
    int  getDiamonds() const { return diamonds; }
    int  getHealth()     const { return health; }
};

#endif // !PLAYER_H