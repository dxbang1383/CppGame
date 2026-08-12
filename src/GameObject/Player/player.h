#ifndef PLAYER_H
#define PLAYER_H

#include <SDL3/SDL.h>
#include "../src/GameObject/gameObject.h"


enum PlayerState {
    STATE_IDLE,
    STATE_RUN,
    STATE_JUMP
};

class player : public gameObject {
private:
    const int playerSize = 48;
    double velocityX = 0.0;
    double velocityY = 0.0;
    double speed = 300.0;
    int direction = 1;
    double gravity = 980.0;
    double jumpForce = 450.0;
    bool onGround = false;
    // Luu sheet dang lam
    SDL_Texture* idleTexture = nullptr; 
    SDL_Texture* runTexture = nullptr;
    SDL_Texture* jumpTexture = nullptr;
    //Trang thai xu li frame cho nhan vat
    PlayerState currentState;
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
    float climbSpeed = 150.0f;

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

    // Di chuyen theo tung truc, dung cho va cham tach truc trong sceneMain
    void moveX(float deltaTime) { setX(getX() + velocityX * deltaTime); }
    void moveY(float deltaTime) { setY(getY() + velocityY * deltaTime); }
    
    void render(SDL_Renderer* renderer) override;
    void update(float deltaTime) override;
};

#endif // !PLAYER_H