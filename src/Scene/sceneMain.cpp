#include "sceneMain.h"
#include "../engine/soundManager.h"

// Constructor
sceneMain::sceneMain() {

}

// Destruction 
sceneMain::~sceneMain() {
                
}

void sceneMain::preLoad(SDL_Renderer* renderer) {
    map.addTextures(renderer); // bkg, platform, decor, enemy, player

    std::string mapPath = std::string(PROJECT_SOURCE_DIR) + "/assets/maps/level1.txt";
    if (!map.load(mapPath)) {
        SDL_Log("Khong nap duoc map: %s -> dung map mac dinh", mapPath.c_str());
    }


    pauseMenu.preLoad(renderer);
    gameOverMenu.preLoad(renderer);
    settings.preLoad(renderer);
    iconTex = resourceManager::getTexture(renderer, "menu");
}

void sceneMain::resetPlayer() {
    player& p = map.getPlayer();
    p.setX(map.getStartX());
    p.setY(map.getStartY());
    p.setVelocityX(0);
    p.setVelocityY(0);
    p.setOnGround(false);
    p.setIsClimbing(false);
    p.setMovingLeft(false);
    p.setMovingRight(false);
    p.setMovingUp(false);
    p.setMovingDown(false);
    p.setDirection(1);
}

void sceneMain::update(float deltaTime) {
    if (paused || lost) return;
    settings.close();

    for (platform& x : map.getPlatforms()) x.update(deltaTime);
    for (decor& d : map.getDecors())       d.update(deltaTime);
    for (flyer& f : map.getFlyers())       f.update(deltaTime);
    for (walker& w : map.getWalkers())     w.update(deltaTime);
    map.getPlayer().update(deltaTime);

    handleCollision(deltaTime);
    handleEnemyCollision();
    focusPlayer();

    map.updateRenderRect();
    for (ladder& l : map.getLadders()) l.updRenderRect(map.getCam());   // thang cũng theo camera

    if (map.getPlayer().getY() > deathY) {
        lost = true;
        soundManager::playEffect("lose");
    }
}

void sceneMain::render(SDL_Renderer* renderer) {
    SDL_FRect bkgRect = { 0, 0, W, H };
    SDL_RenderTexture(renderer, map.getBkg(), nullptr, &bkgRect);

    for (platform& p : map.getPlatforms()) p.render(renderer);
    for (ladder& l : map.getLadders()) l.render(renderer);
    for (decor& d : map.getDecors()) d.render(renderer);
    for (flyer& f : map.getFlyers()) f.render(renderer);
    for (walker& w : map.getWalkers()) w.render(renderer);
    map.getPlayer().render(renderer);

    if (paused) pauseMenu.render(renderer);
    if (lost) gameOverMenu.render(renderer);

    if (!lost) {
        SDL_RenderTexture(renderer, iconTex, paused ? &resumeIconSrc : &pauseIconSrc, &toggleBtnRect);
    }

    if (paused || lost) {
        int base = lost ? 0 : 1;
        float sx = 1220.0f - base * 50.0f;
        SDL_FRect rb = { 1220.0f - (base + 1) * 50.0f, 20.0f, 40.0f, 40.0f };
        SDL_RenderTexture(renderer, iconTex, &iconBSrc, &rb);
        settings.render(renderer, sx, 20.0f);
    }
}

bool sceneMain::overlaps(platform& p) {
    return map.getPlayer().getX() <= p.getX() + p.getWidth()
        && map.getPlayer().getX() + map.getPlayer().getWidth() >= p.getX()
        && map.getPlayer().getY() <= p.getY() + p.getHeight()
        && map.getPlayer().getY() + map.getPlayer().getHeight() >= p.getY();
}

bool sceneMain::overlapsLadder(ladder& l) {
    player& p = map.getPlayer();
    return p.getX() <= l.getX() + l.getWidth()
        && p.getX() + p.getWidth() >= l.getX()
        && p.getY() <= l.getY() + l.getHeight()
        && p.getY() + p.getHeight() >= l.getY();
}

void sceneMain::handleCollision(float deltaTime) {

    player& p = map.getPlayer();

    bool onAnyGround = false;

    for (platform& pl : map.getPlatforms()) {
        if (!overlaps(pl)) continue;

        // Tinh khoang chong lap giua hai truc X va Y
        float overlapLeft = (float)((p.getX() + p.getWidth()) - pl.getX());
        float overlapRight = (float)((pl.getX() + pl.getWidth()) - p.getX());
        float overlapTop = (float)((p.getY() + p.getHeight()) - pl.getY());
        float overlapBottom = (float)((pl.getY() + pl.getHeight()) - p.getY());

        // Tim do sau va cham nho nhat o tung truc
        float minOverlapX = std::min(overlapLeft, overlapRight);
        float minOverlapY = std::min(overlapTop, overlapBottom);

        // Neu overlap X nho hon overlap Y -> va cham TUONG
        if (minOverlapX < minOverlapY) {
            if (overlapLeft < overlapRight)
                p.setX(pl.getX() - p.getWidth());
            else
                p.setX(pl.getX() + pl.getWidth());
            p.setVelocityX(0);
        }
        // Nguoc lai -> va cham SAN hoac TRAN
        else {
            if (overlapTop < overlapBottom) {
                p.setY(pl.getY() - p.getHeight());
                p.setVelocityY(0);
                onAnyGround = true;
            }
            else {
                p.setY(pl.getY() + pl.getHeight());
                p.setVelocityY(0);
            }
        }
    }

    // --- Thang ---
    bool touchingLadder = false;
    for (ladder& l : map.getLadders()) {
        if (overlapsLadder(l)) {
            touchingLadder = true;
            break;   // Chi can cham vao 1 nac la du
        }
    }

    // Cap nhat trang thai cho Player
    p.setIsTouchingLadder(touchingLadder);

    // Roi khoi thang thi thoi leo (ban cu thieu -> treo lo lung giua khong trung)
    if (!touchingLadder) p.setIsClimbing(false);

    // Neu dang treo thang thi khong can xu li voi mat dat
    if (p.getIsClimbing()) return;

    // Cap nhat lai trang thai dung tren mat dat cho player
    p.setOnGround(onAnyGround);
}

void sceneMain::handleEnemyCollision() {
    player& p = map.getPlayer();
    float px = p.getX(), py = p.getY(), pw = p.getWidth(), ph = p.getHeight();

    for (walker& w : map.getWalkers()) {
        float wx = w.getX() + w.getInsetSide();
        float wy = w.getY() + w.getInsetTop();
        float ww = w.getWidth() - 2 * w.getInsetSide();
        float wh = w.getHeight() - w.getInsetTop();

        bool over = px <= wx + ww && px + pw >= wx && py <= wy + wh && py + ph >= wy;
        if (!over) continue;

        float overlapLeft = (px + pw) - wx;
        float overlapRight = (wx + ww) - px;
        float overlapTop = (py + ph) - wy;
        float overlapBottom = (wy + wh) - py;
        float minX = std::min(overlapLeft, overlapRight);
        float minY = std::min(overlapTop, overlapBottom);

        int side;
        if (minX < minY) {
            if (overlapLeft < overlapRight) { p.setX(wx - pw); side = 0; }
            else { p.setX(wx + ww); side = 1; }
            p.setVelocityX(0);
        }
        else {
            if (overlapTop < overlapBottom) { p.setY(wy - ph); p.setOnGround(true); side = 2; }
            else { p.setY(wy + wh); side = 3; }
            p.setVelocityY(0);
        }

        px = p.getX(); py = p.getY();

        int k = w.getKind();
        if (k == 1) {
            w.stop();
            if (side == 2) lost = true;
        }
        else if (k == 2) {
            w.stop();
            if (side != 2) lost = true;
        }
        else if (k == 3) {
            if (side == 2) w.stop();
        }
    }
}

// xá»­ lÃ½ input 
void sceneMain::handleInput(const SDL_Event& event) {
    if ((paused || lost)
        && event.type == SDL_EVENT_MOUSE_BUTTON_DOWN
        && event.button.button == SDL_BUTTON_LEFT) {
        int base = lost ? 0 : 1;
        float sx = 1220.0f - base * 50.0f;
        if (settings.handleClick(event.button.x, event.button.y, sx, 20.0f)) return;
    }

    if (lost) {
        if (event.type == SDL_EVENT_MOUSE_MOTION) {
            gameOverMenu.handleMouseMove(event.motion.x, event.motion.y);
        }
        else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN
                 && event.button.button == SDL_BUTTON_LEFT) {
            gameOverMenu.handleClick(event.button.x, event.button.y);
            int a = gameOverMenu.getAction();
            if (a == GAMEOVER_REPLAY)     { resetPlayer(); lost = false; }
            else if (a == GAMEOVER_MODE2) { resetPlayer(); lost = false; sceneAction = SCENE_EDITOR; }
            else if (a == GAMEOVER_MENU)  { resetPlayer(); lost = false; sceneAction = SCENE_MENU; }
            else if (a == GAMEOVER_QUIT)  { sceneAction = SCENE_QUIT; }
            gameOverMenu.resetAction();
        }
        return;
    }

    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN
        && event.button.button == SDL_BUTTON_LEFT
        && event.button.x >= toggleBtnRect.x && event.button.x <= toggleBtnRect.x + toggleBtnRect.w
        && event.button.y >= toggleBtnRect.y && event.button.y <= toggleBtnRect.y + toggleBtnRect.h) {
        paused = !paused;
        pauseMenu.resetAction();
        return;
    }

    if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_P) {
        paused = !paused;
        pauseMenu.resetAction();
        return;
    }

    if (paused) {
        if (event.type == SDL_EVENT_MOUSE_MOTION) {
            pauseMenu.handleMouseMove(event.motion.x, event.motion.y);
        }
        else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN
                 && event.button.button == SDL_BUTTON_LEFT) {
            pauseMenu.handleClick(event.button.x, event.button.y);
            int a = pauseMenu.getAction();
            if (a == PAUSE_RESUME)      paused = false;
            else if (a == PAUSE_REPLAY) { resetPlayer(); paused = false; }
            else if (a == PAUSE_MENU)   { resetPlayer(); sceneAction = SCENE_MENU; paused = false; }
            else if (a == PAUSE_QUIT)   sceneAction = SCENE_QUIT;
            pauseMenu.resetAction();
        }
        return;
    }

    if (event.type == SDL_EVENT_KEY_DOWN) {
        switch (event.key.key) {
        case SDLK_A:
        case SDLK_LEFT:
            map.getPlayer().setDirection(-1);
            map.getPlayer().setMovingLeft(true);
            break;
        case SDLK_D:
        case SDLK_RIGHT:
            map.getPlayer().setMovingRight(true);
            map.getPlayer().setDirection(1);
            break;
        case SDLK_SPACE:
        case SDLK_W:
        case SDLK_UP:
            if (map.getPlayer().IsTouchingLadder()) {
                map.getPlayer().setIsClimbing(true);
                map.getPlayer().setOnGround(false);
                map.getPlayer().setMovingUp(true);
            } else if (map.getPlayer().isOnGround()) {
                map.getPlayer().setVelocityY(-map.getPlayer().getJumpForce());
                map.getPlayer().setOnGround(false);
            }
            break;  
        case SDLK_S:
        case SDLK_DOWN:
            if (map.getPlayer().IsTouchingLadder()) {
                map.getPlayer().setIsClimbing(true);
                map.getPlayer().setMovingDown(true);
            }
            break;
        case SDLK_L:
            map.load(std::string(PROJECT_SOURCE_DIR) + "/assets/maps/level1.txt");
            std::cout << "load " << std::endl;
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
        case SDLK_SPACE:
        case SDLK_W:
        case SDLK_UP:
            if (map.getPlayer().IsTouchingLadder()) {
                map.getPlayer().setMovingUp(false);
            }
            break;
        case SDLK_S:
        case SDLK_DOWN:
            if (map.getPlayer().IsTouchingLadder()) {
                map.getPlayer().setMovingDown(false);
            }
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