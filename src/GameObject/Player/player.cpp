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
}

player::player() : player(0.0, 0.0, 32.0, 32.0) {}

// --- XỬ LÝ PHÍM ĐIỀU KIỂN ---
void player::handleInput(const SDL_Event& event) {
    // 1. Khi BẤM phím down
    if (event.type == SDL_EVENT_KEY_DOWN) {
        switch (event.key.key) {
        case SDLK_A:
        case SDLK_LEFT:
            isMovingLeft = true;
            setDirection(-1);
            break;
        case SDLK_D:
        case SDLK_RIGHT:
            isMovingRight = true;
            setDirection(1);
            break;
        case SDLK_SPACE:
        case SDLK_W:
        case SDLK_UP:
            // Chỉ cho phép nhảy khi đang đứng trên mặt đất
            if (onGround) {
                velocityY = -jumpForce; // Dấu âm để đi lên trên
                onGround = false;
            }
            break;
        }
    }
    // 2. Khi THẢ phím up
    else if (event.type == SDL_EVENT_KEY_UP) {
        switch (event.key.key) {
        case SDLK_A:
        case SDLK_LEFT:
            isMovingLeft = false;
            break;
        case SDLK_D:
        case SDLK_RIGHT:
            isMovingRight = false;
            break;
        }
    }
}

void player::update(float deltaTime) {
    // A. Tính toán vận tốc ngang (X) dựa trên phím bấm
    velocityX = 0.0;
    if (isMovingLeft)  velocityX -= speed;
    if (isMovingRight) velocityX += speed;

    // B. Tính toán trọng trường (Y)
    if (!onGround) {
        velocityY += gravity * deltaTime;
    }
    else {
        if (velocityY > 0) velocityY = 0.0; // Reset vận tốc rơi khi đáp đất
    }

    // C. Cập nhật vị trí
    setX(getX() + velocityX * deltaTime);
    setY(getY() + velocityY * deltaTime);

    // Đồng bộ với SDL_FRect
    udpRect();
}

void player::render(SDL_Renderer* renderer) {
    if (renderer == nullptr) return;

    SDL_Texture* tex = getTexture();
    SDL_FRect* pRect = getRect();

    if (tex != nullptr) {
        SDL_FlipMode flipMode = (direction < 0) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
        SDL_RenderTextureRotated(renderer, tex, NULL, pRect, 0.0, NULL, flipMode);
    }
    else {
        // Vẽ khối màu đỏ đại diện cho nhân vật
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