#include "sceneMain.h"

sceneMain::sceneMain()
    : mainPlayer(100.0, 100.0, 50.0, 50.0) 
{
    for (int x = 0; x < 26; x++)
        plat.emplace_back(x, 14, "P");

    plat.emplace_back(3, 13, "P");
    plat.emplace_back(4, 12, "P");
    plat.emplace_back(5, 11, "P");
    plat.emplace_back(6, 10, "P");

    for (int x = 6; x <= 12; x++)
        plat.emplace_back(x, 10, "map1", 2, 4);

    plat.emplace_back(13, 9, "P");
    plat.emplace_back(14, 8, "map1", 14, 1, "x++");
    plat.emplace_back(14, 9, "map1", 14, 2, "x++");
    plat.emplace_back(14, 10, "map1", 14, 2, "x++");
    decorList.emplace_back(9, 9, "map1", 11, 7, "x++");
    plat.emplace_back(15, 7, "P");

    for (int x = 15; x <= 21; x++)
        plat.emplace_back(x, 7, "P");

    plat.emplace_back(22, 8, "P");
    plat.emplace_back(23, 9, "P");
    plat.emplace_back(24, 10, "P");

    for (int x = 21; x <= 25; x++)
        plat.emplace_back(x, 11, "P");
}

sceneMain::~sceneMain() {

}

// tải tài nguyên trước khi vào màn 
void sceneMain::preLoad(SDL_Renderer* renderer) {
    /*
    bkg = resourceManager::loadImage(renderer, "default");
    p1 = resourceManager::loadImage(renderer, "P");
    p2 = resourceManager::loadImage(renderer, "player");
    map1 = resourceManager::loadImage(renderer, "map1");
    */

    // Backgrond
    bkg = resourceManager::getTexture(renderer, "bkg");

    // platform
    for (platform& x : plat) {
        /*
        if (x.getType() == "P") {
            x.setTexture(p1);
        }
        else if (x.getType() == "map1") {
            x.setTexture(map1);
        }
        */

        x.setTexture(resourceManager::getTexture(renderer, x.getType()));
    }

    for (decor& d : decorList) {
        d.setTexture(resourceManager::getTexture(renderer, d.getType()));
    }

    mainPlayer.setTexture(resourceManager::getTexture(renderer, "player"));

    // mainPlayer.setTexture(p2);
}

// cập nhật mỗi vòng lặp 
void sceneMain::update(float deltaTime) {

    for (platform& x : plat) {
        x.update(deltaTime);
    }

    for (decor& d : decorList) {
        d.update(deltaTime);
    }
  
    mainPlayer.update(deltaTime);
    /* 
    float groundLevel = 500.0f - mainPlayer.getHeight();

    if (mainPlayer.getY() >= groundLevel) {
        mainPlayer.setY(groundLevel);      
        mainPlayer.setOnGround(true);    
    }
    else {
        mainPlayer.setOnGround(false);      
    }*/
    handleCollision();
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

    mainPlayer.render(renderer);


    // vẽ dường kẻ 

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
    }
}

// xử lý va chạm 
void sceneMain::handleCollision() {
    for (platform& p : plat) {
        // bien nay chi check xem co va cham khong
        bool check = mainPlayer.getX() < p.getX() + p.getWidth()
            && mainPlayer.getX() + mainPlayer.getWidth() > p.getX()
            && mainPlayer.getY() < p.getY() + p.getHeight()
            && mainPlayer.getY() + mainPlayer.getHeight() > p.getY();
        if (check == true) {
            //std::cout << "co va cham nguoi choi voi platform di vao xu ly va cham" << std::endl;
            // neu va cham theo phuong thang dung
            mainPlayer.setY(p.getY() - mainPlayer.getHeight());
            mainPlayer.setOnGround(true);
            return;
        }
    }
    mainPlayer.setOnGround(false);
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

void sceneMain::switchScene() {
    //sau nay khoi tao nhan sk ban phim 
}