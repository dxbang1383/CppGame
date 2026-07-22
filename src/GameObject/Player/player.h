#ifndef PLAYER_H
#define PLAYER_H

#include <SDL3/SDL.h>
#include "../src/GameObject/gameObject.h"

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

    // Trạng thái nút bấm
    bool isMovingLeft = false;
    bool isMovingRight = false;

public:
    player(double x, double y, double width, double height);
    player(double x, double y);
    player();

    int getDirection();
    void setSpeed(double speed);
    void setDirection(int d);
    void setOnGround(bool grounded);
    bool isOnGround() const;
    void setMovingLeft(bool left);
    void setMovingRight(bool right);
    void setVelocityX(double x);
    void setVelocityY(double y);
    double getJumpForce();

    void render(SDL_Renderer* renderer) override;
    void update(float deltaTime) override;
};

#endif // !PLAYER_H