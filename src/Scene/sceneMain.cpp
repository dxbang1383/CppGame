#include "sceneMain.h"

// Constructor ( tạm thời khởi tạo map tại đây )
sceneMain::sceneMain()
    : mainPlayer(100.0, 100.0, 50.0, 50.0) 
{
    for (int x = 0; x < 26; x++)
        plat.emplace_back(x, 14, "map1", 2, 4);

    plat.emplace_back(3, 13, "map1", 2, 4);
    plat.emplace_back(4, 12, "map1", 2, 4);
    plat.emplace_back(5, 11, "map1", 2, 4);
    plat.emplace_back(6, 10, "map1", 2, 4);

    for (int x = 6; x <= 12; x++)
        plat.emplace_back(x, 10, "map1", 2, 4);

    plat.emplace_back(13, 9, "map1", 2, 4);
    plat.emplace_back(14, 8, "map1", 14, 1, "x++");
    plat.emplace_back(14, 9, "map1", 14, 2, "x++");
    plat.emplace_back(14, 10, "map1", 14, 2, "x++");
    decorList.emplace_back(9, 9, "map1", 11, 7, "x++");
    plat.emplace_back(15, 7, "map1", 2, 4);

    for (int x = 15; x <= 21; x++)
        plat.emplace_back(x, 7, "map1", 2, 4);

    plat.emplace_back(22, 8, "map1", 2, 4);
    plat.emplace_back(23, 9, "map1", 2, 4);
    plat.emplace_back(24, 10, "map1", 2, 4);

    for (int x = 21; x <= 25; x++)
        plat.emplace_back(x, 11, "map1", 2, 4);

    SDL_srand(0);
    double ex = 100.0 + SDL_rand(700);
    double ey = 50.0  + SDL_rand(250);
    enemies.emplace_back(ex, ey, 40.0, 40.0);
}

// Destruction 
sceneMain::~sceneMain() {

}

// tải tài nguyên trước khi vào màn 
void sceneMain::preLoad(SDL_Renderer* renderer) {

    // Backgrond
    bkg = resourceManager::getTexture(renderer, "bkg");

    // platform
    for (platform& x : plat) {
        x.setTexture(resourceManager::getTexture(renderer, x.getType()));
    }

    for (decor& d : decorList) {
        d.setTexture(resourceManager::getTexture(renderer, d.getType()));
    }

    mainPlayer.setTexture(resourceManager::getTexture(renderer, "player"));

    for (enemy& e : enemies)
        e.setTexture(resourceManager::getTexture(renderer, "enemy"));

}

// cập nhật mỗi vòng lặp 
void sceneMain::update(float deltaTime) {
    // cập nhật vị trí trong thế giới
    for (platform& x : plat) x.update(deltaTime);
    for (decor& d : decorList) d.update(deltaTime);
    mainPlayer.update(deltaTime);
    for (enemy& e : enemies) e.update(deltaTime);

    handleCollision(deltaTime);

    focusPlayer(); // camera chốt vị trí
    
    // rồi mới tính lại renderRect cho mọi object
    for (platform& x : plat) x.updRenderRect(cam);
    for (decor& d : decorList) d.updRenderRect(cam);
    mainPlayer.updRenderRect(cam);
    for (enemy& e : enemies) e.updRenderRect(cam);
}

// in ra bên ngoài 
void sceneMain::render(SDL_Renderer* renderer) {
    //std::cout << "ground :" << mainPlayer.isOnGround() << std::endl;
    
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_FRect groundRect = { 0.0f, 500.0f, 1280.0f, 220.0f };
    SDL_RenderFillRect(renderer, &groundRect);

    SDL_FRect bkgRect = { 0, 0, 1280, 720 };
    SDL_RenderTexture(renderer, bkg, nullptr, &bkgRect);

    for (platform& p : plat)
        p.render(renderer);

    for (decor& d : decorList) {
        d.render(renderer);
    }

    for (enemy& e : enemies) e.render(renderer);
    mainPlayer.render(renderer);


    // vẽ dường kẻ 
    /*
    // kẻ
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 50);
    for (int c = 0; c <= COLS; c++)
        SDL_RenderLine(renderer, c * TILE, 0.0f, c * TILE, H);
    for (int r = 0; r <= ROWS; r++)
        SDL_RenderLine(renderer, 0.0f, r * TILE, W, r * TILE);

    // toa do
    
    char buf[16];
    SDL_SetRenderDrawColor(renderer, 0 , 0, 0, 160);
    for (int c = 0; c < COLS; c++) {
        for (int r = 0; r < ROWS; r++) {
            SDL_snprintf(buf, sizeof(buf), "%d,%d", c % 10, r % 10);
            SDL_RenderDebugText(renderer, c * TILE + 2.0f, r * TILE + 2.0f, buf);
        }
    }*/
}

bool sceneMain::overlaps(platform& p) {
    return mainPlayer.getX() < p.getX() + p.getWidth()
        && mainPlayer.getX() + mainPlayer.getWidth() > p.getX()
        && mainPlayer.getY() < p.getY() + p.getHeight()
        && mainPlayer.getY() + mainPlayer.getHeight() > p.getY();
}

void sceneMain::handleCollision(float deltaTime) {
    //Ngang
    mainPlayer.moveX(deltaTime);
    for (platform& p : plat) {
        if (!overlaps(p)) continue;
        if (mainPlayer.getVelocityX() > 0)
            mainPlayer.setX(p.getX() - mainPlayer.getWidth());
        else if (mainPlayer.getVelocityX() < 0)
            mainPlayer.setX(p.getX() + p.getWidth());
        mainPlayer.setVelocityX(0);
    }

    //Dọc
    mainPlayer.moveY(deltaTime);
    mainPlayer.setOnGround(false);
    for (platform& p : plat) {
        if (!overlaps(p)) continue;
        if (mainPlayer.getVelocityY() > 0) {
            mainPlayer.setY(p.getY() - mainPlayer.getHeight());
            mainPlayer.setOnGround(true);
        }
        else if (mainPlayer.getVelocityY() < 0) {
            mainPlayer.setY(p.getY() + p.getHeight());
        }
        mainPlayer.setVelocityY(0);
    }
}


// xử lý input 
void sceneMain::handleInput(const SDL_Event& event) {


    if (event.type == SDL_EVENT_KEY_DOWN) {
        switch (event.key.key) {
        case SDLK_A:
        case SDLK_LEFT:
            mainPlayer.setMovingLeft(true);
            mainPlayer.setDirection(-1);
            break;
        case SDLK_D:
        case SDLK_RIGHT:
            mainPlayer.setMovingRight(true);
            mainPlayer.setDirection(1);
            break;
        case SDLK_SPACE:
        case SDLK_W:
        case SDLK_UP:
            if (mainPlayer.isOnGround()) {
                mainPlayer.setVelocityY(- mainPlayer.getJumpForce());
                mainPlayer.setOnGround(false);
            }
            break;
        }
    }

    else if (event.type == SDL_EVENT_KEY_UP) {
        switch (event.key.key) {
        case SDLK_A:
        case SDLK_LEFT:
            mainPlayer.setMovingLeft(false);
            break;
        case SDLK_D:
        case SDLK_RIGHT:
            mainPlayer.setMovingRight(false);
            break;
        }
    }

}

void sceneMain::focusPlayer() {
    cam.focus(mainPlayer.getX(), mainPlayer.getY(), W, H);
}

void sceneMain::switchScene() {
    //sau nay khoi tao nhan sk ban phim 
}