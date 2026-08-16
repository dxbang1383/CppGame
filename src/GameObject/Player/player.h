#ifndef PLAYER_H
#define PLAYER_H

#include <SDL3/SDL.h>
#include <iostream>
#include "../src/GameObject/gameObject.h"


enum class PlayerState {
    STATE_IDLE,
    STATE_RUN,
    STATE_JUMP
};

class player : public gameObject {
private:
    const int playerSize = 48; // kich cỡ nhân vật
    double velocityX = 0.0; // vận tốc theo trục x 
    double velocityY = 0.0; // vận tốc theo trục y 
    double speed = 300.0; // tốc độ của nhân vật
    int direction = 1; // hướng của nhân vật 
    double gravity = 980.0; // tốc độ của trọng lực
    double jumpForce = 1000.0; // tốc độ nhảy 
    bool onGround = false; // trêm mặt đất hay không 
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
    void setOnGround(bool grounded) { this->onGround = grounded; }
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
    // Ham sceneMain nap anh vao cho player
    void setIdleTexture(SDL_Texture* tex) {
        this->idleTexture = tex;
    }
    void setRunTexture(SDL_Texture* tex) {
        this->runTexture = tex;
    }
    void setJumpTexture(SDL_Texture* tex) {
        this->jumpTexture = tex;
    }
    void setIsTouchingLadder(bool touch) { isTouchingLadder = touch; }
    bool IsTouchingLadder() const { return this->isTouchingLadder; }
    bool getIsClimbing() { return isClimbing; }
    void setIsClimbing(bool climbing) { isClimbing = climbing; }

    SDL_Texture* getIdleTexture() const { return idleTexture; }
    SDL_Texture* getRunTexture() const { return runTexture; }
    SDL_Texture* getJumpTexture() const { return jumpTexture; }
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
};

#endif // !PLAYER_H