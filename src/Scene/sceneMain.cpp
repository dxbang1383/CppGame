#include "sceneMain.h"

// Constructor ( tạm thời khởi tạo map tại đây )
sceneMain::sceneMain()
{
}

// Destruction 
sceneMain::~sceneMain() {

}

// tải tài nguyên trước khi vào màn 
void sceneMain::preLoad(SDL_Renderer* renderer) {
    map.addTextures(renderer);
}

// cập nhật mỗi vòng lặp 
void sceneMain::update(float deltaTime) {
    // cập nhật vị trí trong thế giới
    for (platform& x : map.getPlatforms()) x.update(deltaTime);
    for (decor& d : map.getDecors()) d.update(deltaTime);
    map.getPlayer().update(deltaTime);
    for (enemy& e : map.getEnemies()) e.update(deltaTime);

    handleCollision(deltaTime);

    focusPlayer(); // camera chốt vị trí
    
    // rồi mới tính lại renderRect cho mọi object
    map.updateRenderRect();
}

// in ra bên ngoài 
void sceneMain::render(SDL_Renderer* renderer) {
    //std::cout << "ground :" << mainPlayer.isOnGround() << std::endl;
    
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_FRect groundRect = { 0.0f, 500.0f, 1280.0f, 220.0f };
    SDL_RenderFillRect(renderer, &groundRect);

    SDL_FRect bkgRect = { 0, 0, 1280, 720 };
    SDL_RenderTexture(renderer, map.getBkg(), nullptr, &bkgRect);

    for (platform& p : map.getPlatforms())
        p.render(renderer);

    for (decor& d : map.getDecors()) {
        d.render(renderer);
    }

    for (enemy& e : map.getEnemies()) e.render(renderer);
    map.getPlayer().render(renderer);

}

bool sceneMain::overlaps(platform& p) {
    return map.getPlayer().getX() < p.getX() + p.getWidth()
        && map.getPlayer().getX() + map.getPlayer().getWidth() > p.getX()
        && map.getPlayer().getY() < p.getY() + p.getHeight()
        && map.getPlayer().getY() + map.getPlayer().getHeight() > p.getY();
}

void sceneMain::handleCollision(float deltaTime) {
    //Ngang
    map.getPlayer().moveX(deltaTime);
    for (platform& p : map.getPlatforms()) {
        if (!overlaps(p)) continue;
        if (map.getPlayer().getVelocityX() > 0)
            map.getPlayer().setX(p.getX() - map.getPlayer().getWidth());
        else if (map.getPlayer().getVelocityX() < 0)
            map.getPlayer().setX(p.getX() + p.getWidth());
        map.getPlayer().setVelocityX(0);
    }

    //Dọc
    map.getPlayer().moveY(deltaTime);
    map.getPlayer().setOnGround(false);
    for (platform& p : map.getPlatforms()) {
        if (!overlaps(p)) continue;
        if (map.getPlayer().getVelocityY() > 0) {
            map.getPlayer().setY(p.getY() - map.getPlayer().getHeight());
            map.getPlayer().setOnGround(true);
        }
        else if (map.getPlayer().getVelocityY() < 0) {
            map.getPlayer().setY(p.getY() + p.getHeight());
        }
        map.getPlayer().setVelocityY(0);
    }
}


// xử lý input 
void sceneMain::handleInput(const SDL_Event& event) {
    if (event.type == SDL_EVENT_KEY_DOWN) {
        switch (event.key.key) {
        case SDLK_A:
        case SDLK_LEFT:
            map.getPlayer().setMovingLeft(true);
            map.getPlayer().setDirection(-1);
            break;
        case SDLK_D:
        case SDLK_RIGHT:
            map.getPlayer().setMovingRight(true);
            map.getPlayer().setDirection(1);
            break;
        case SDLK_SPACE:
        case SDLK_W:
        case SDLK_UP:
            if (map.getPlayer().isOnGround()) {
                map.getPlayer().setVelocityY(-map.getPlayer().getJumpForce());
                map.getPlayer().setOnGround(false);
            }
            break;
        }
    }

    else if (event.type == SDL_EVENT_KEY_UP) {
        switch (event.key.key) {
        case SDLK_A:
        case SDLK_LEFT:
            map.getPlayer().setMovingLeft(false);
            break;
        case SDLK_D:
        case SDLK_RIGHT:
            map.getPlayer().setMovingRight(false);
            break;
        }
    }

}

void sceneMain::focusPlayer() {
    map.getCam().focus(map.getPlayer().getX(), map.getPlayer().getY(), W, H);
}

void sceneMain::switchScene() {
    //sau nay khoi tao nhan sk ban phim 
}