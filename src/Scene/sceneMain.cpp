#include "sceneMain.h"

// Constructor ( táº¡m thá»i khá»Ÿi táº¡o map táº¡i Ä‘Ã¢y )
sceneMain::sceneMain()
{
    for (int x = 0; x < 26; x++)
        plat.emplace_back(x, 14, "P");

    plat.emplace_back(3, 13, "P");
    plat.emplace_back(4, 12, "P");
    plat.emplace_back(5, 11, "P");
    plat.emplace_back(6, 10, "P");

    for (int x = 6; x <= 12; x++)
        plat.emplace_back(x, 10, "P");

    plat.emplace_back(13, 9, "P");
    plat.emplace_back(14, 8, "P");
    plat.emplace_back(15, 7, "P");

    for (int x = 15; x <= 21; x++)
        plat.emplace_back(x, 7, "P");

    plat.emplace_back(22, 8, "P");
    plat.emplace_back(23, 9, "P");
    plat.emplace_back(24, 10, "P");

    for (int x = 21; x <= 25; x++)
        plat.emplace_back(x, 11, "P");

    int ladderX = 10;
    for (int y = 9; y <= 13; y++) {
        ladders.emplace_back(ladderX * 32, y * 32.0, 32.0, 32.0);
    }
}

// Destruction 
sceneMain::~sceneMain() {
                
}

// táº£i tÃ i nguyÃªn trÆ°á»›c khi vÃ o mÃ n 
void sceneMain::preLoad(SDL_Renderer* renderer) {
    bkg = resourceManager::loadImage(renderer, "default");
    p1 = resourceManager::loadImage(renderer, "P");
    p2 = resourceManager::loadImage(renderer, "player");
    p3 = resourceManager::loadImage(renderer, "player_idle");
    p4 = resourceManager::loadImage(renderer, "player_run");
    p5 = resourceManager::loadImage(renderer, "player_jump");
    p6 = resourceManager::loadImage(renderer, "ladder");

    // Gan truc tiep vao player
    for (ladder& l : ladders) {
        l.setTexture(p6);
    }
    for (platform& x : plat) {
        if (x.getType() == "P")
            x.setTexture(p1);
    }

    mainPlayer.setIdleTexture(p3 != nullptr ? p3 : p2);
    mainPlayer.setRunTexture(p4 != nullptr ? p4 : p2);
    mainPlayer.setJumpTexture(p5 != nullptr ? p5 : p2);
    mainPlayer.setTexture(p3 != nullptr ? p3 : p2);
    map.addTextures(renderer);
}

// cáº­p nháº­t má»—i vÃ²ng láº·p 
void sceneMain::update(float deltaTime) {
  
    mainPlayer.update(deltaTime);
    handleCollision();
}
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

// in ra bÃªn ngoÃ i 
void sceneMain::render(SDL_Renderer* renderer) {
    
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_FRect groundRect = { 0.0f, 500.0f, 1280.0f, 220.0f };
    SDL_RenderFillRect(renderer, &groundRect);

    SDL_FRect bkgRect = { 0, 0, 1280, 720 };
    SDL_RenderTexture(renderer, map.getBkg(), nullptr, &bkgRect);

    for (platform& p : map.getPlatforms())
        p.render(renderer);
    for (ladder& l : ladders)
        l.render(renderer);

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
void sceneMain::handleCollision() {
    bool onAnyGround = false;

    for (platform& p : plat) {
        bool isColliding = mainPlayer.getX() < p.getX() + p.getWidth()
            && mainPlayer.getX() + mainPlayer.getWidth() > p.getX()
            && mainPlayer.getY() < p.getY() + p.getHeight()
            && mainPlayer.getY() + mainPlayer.getHeight() > p.getY();

        if (isColliding) {
            // Tinh khoang chong lap giua hai truc X va Y
            float overlapLeft   = (mainPlayer.getX() + mainPlayer.getWidth()) - p.getX();
            float overlapRight  = (p.getX() + p.getWidth()) - mainPlayer.getX();
            float overlapTop    = (mainPlayer.getY() + mainPlayer.getHeight()) - p.getY();
            float overlapBottom = (p.getY() + p.getHeight()) - mainPlayer.getY();

            // Tim do sau va cham nho nhat o tung truc
            float minOverlapX = std::min(overlapLeft, overlapRight);
            float minOverlapY = std::min(overlapTop, overlapBottom);

            // So sanh neu Overlap X nho hon overLap Y -> va cham Tuong

            if (minOverlapX < minOverlapY) {
                if (overlapLeft < overlapRight) {
                    mainPlayer.setX(p.getX() - mainPlayer.getWidth());
                }
                else {
                    mainPlayer.setX(p.getX() + p.getWidth());
                }
                mainPlayer.setVelocityX(0);
            }
            // Va cham doc san tran 
            else {
                if (overlapTop < overlapBottom) {
                    mainPlayer.setY(p.getY() - mainPlayer.getHeight());
                    mainPlayer.setVelocityY(0);
                    onAnyGround = true;
                }
                else {
                    mainPlayer.setY(p.getY() + p.getHeight());
                    mainPlayer.setVelocityY(0);
                }
            }
        }
    }

    bool touchingLadder = false;
    for (ladder& l : ladders) {
        bool isOverlap = mainPlayer.getX() < l.getX() + l.getWidth()
            && mainPlayer.getX() + mainPlayer.getWidth() > l.getX()
            && mainPlayer.getY() < l.getY() + l.getHeight()
            && mainPlayer.getY() + mainPlayer.getHeight() > l.getY();

        if (isOverlap) {
            touchingLadder = true;
            break; // Ch? c?n ch?m vào 1 n?c là ??
        }
    }
    //Cap nhat trang thai cho Player
    mainPlayer.setIsTouchingLadder(touchingLadder);

    //Neu dang treo thang khong can xu li voi platform cung
    if (mainPlayer.getIsClimbing()) {
        return;
    }
    // Cap nhat lai trang thai dung tren mat dat cho player
    mainPlayer.setOnGround(onAnyGround);
}


// xá»­ lÃ½ input 
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
            if (mainPlayer.IsTouchingLadder()) {
                mainPlayer.setIsClimbing(true);
                mainPlayer.setMovingUp(true);
            } else if (mainPlayer.isOnGround()) {
                mainPlayer.setVelocityY(-mainPlayer.getJumpForce());
                mainPlayer.setOnGround(false);
            }
            break;  
        case SDLK_S:
        case SDLK_DOWN:
            if (mainPlayer.IsTouchingLadder()) {
                mainPlayer.setIsClimbing(true);
                mainPlayer.setMovingUp(true);
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