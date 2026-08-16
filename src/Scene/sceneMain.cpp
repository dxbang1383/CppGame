#include "sceneMain.h"
// Constructor
sceneMain::sceneMain() {
// Map da tu dung san trong constructor cua no
// =========================================================
// LADDER
// =========================================================

// Cầu thang 1: nối platform ở row 25 -> row 21
    int ladderCol = 12;

    for (int row = 21; row <= 25; row++) {
        ladders.emplace_back(
            ladderCol * platform::TILE_SIZE,
            row * platform::TILE_SIZE,
            platform::TILE_SIZE,
            platform::TILE_SIZE
        );
    }

    // Cầu thang 2: nối khu vực giữa map
    ladderCol = 20;

    for (int row = 16; row <= 20; row++) {
        ladders.emplace_back(
            ladderCol * platform::TILE_SIZE,
            row * platform::TILE_SIZE,
            platform::TILE_SIZE,
            platform::TILE_SIZE
        );
    }

    // Cầu thang 3: khu vực cao
    ladderCol = 27;

    for (int row = 12; row <= 16; row++) {
        ladders.emplace_back(
            ladderCol * platform::TILE_SIZE,
            row * platform::TILE_SIZE,
            platform::TILE_SIZE,
            platform::TILE_SIZE
        );
    }

    // Cầu thang 4: gần cuối map
    ladderCol = 53;

    for (int row = 15; row <= 20; row++) {
        ladders.emplace_back(
            ladderCol * platform::TILE_SIZE,
            row * platform::TILE_SIZE,
            platform::TILE_SIZE,
            platform::TILE_SIZE
        );
    }


    // =========================================================
    // SWITCH
    // =========================================================

    // Switch 1: khu vực đầu map
    map.getSwitches().emplace_back(
        10 * platform::TILE_SIZE,
        20 * platform::TILE_SIZE,
        platform::TILE_SIZE,
        platform::TILE_SIZE
    );

    // Switch 2: khu vực giữa map
    map.getSwitches().emplace_back(
        27 * platform::TILE_SIZE,
        11 * platform::TILE_SIZE,
        platform::TILE_SIZE,
        platform::TILE_SIZE
    );

    // Switch 3: gần cuối map
    map.getSwitches().emplace_back(
        50 * platform::TILE_SIZE,
        19 * platform::TILE_SIZE,
        platform::TILE_SIZE,
        platform::TILE_SIZE
    );


    // =========================================================
    // SPIKE
    // =========================================================

    // Bẫy 1: sau khu vực platform đầu
    for (int col = 11; col <= 13; col++) {
        spikes.emplace_back(
            col * platform::TILE_SIZE,
            20 * platform::TILE_SIZE,
            platform::TILE_SIZE,
            platform::TILE_SIZE
        );
    }

    // Bẫy 2: khu vực giữa map
    for (int col = 28; col <= 31; col++) {
        spikes.emplace_back(
            col * platform::TILE_SIZE,
            20 * platform::TILE_SIZE,
            platform::TILE_SIZE,
            platform::TILE_SIZE
        );
    }

    // Bẫy 3: khu vực cầu
    for (int col = 37; col <= 38; col++) {
        spikes.emplace_back(
            col * platform::TILE_SIZE,
            20 * platform::TILE_SIZE,
            platform::TILE_SIZE,
            platform::TILE_SIZE
        );
    }

    // Bẫy 4: gần cuối map
    for (int col = 46; col <= 49; col++) {
        spikes.emplace_back(
            col * platform::TILE_SIZE,
            20 * platform::TILE_SIZE,
            platform::TILE_SIZE,
            platform::TILE_SIZE
        );
    }
}

// Destruction 
sceneMain::~sceneMain() {
                
}

void sceneMain::preLoad(SDL_Renderer* renderer) {
    map.addTextures(renderer);          // bkg, platform, decor, enemy, player

    // Animation player
    SDL_Texture* idle = resourceManager::getTexture(renderer, "player_idle");
    SDL_Texture* run = resourceManager::getTexture(renderer, "player_run");
    SDL_Texture* jump = resourceManager::getTexture(renderer, "player_jump");
    SDL_Texture* def = resourceManager::getTexture(renderer, "player");

    player& p = map.getPlayer();
    p.setIdleTexture(idle ? idle : def);
    p.setRunTexture(run ? run : def);
    p.setJumpTexture(jump ? jump : def);
    p.setTexture(idle ? idle : def);

    // Thang
    SDL_Texture* ladTex = resourceManager::getTexture(renderer, "ladder");
    for (ladder& l : ladders) l.setTexture(ladTex);

    SDL_Texture* switchTex = resourceManager::getTexture(renderer, "switch");
    for (Switch& sw : map.getSwitches()) {
        sw.setTexture(switchTex);
    }

    SDL_Texture* spikeTex = resourceManager::getTexture(renderer, "spike");
    for (spike& sp : spikes) {
        sp.setTexture(spikeTex);
    }
}

void sceneMain::update(float deltaTime) {
    for (platform& x : map.getPlatforms())    x.update(deltaTime);
    for (decor& d    : map.getDecors())       d.update(deltaTime);
    for (enemy& e    : map.getEnemies())      e.update(deltaTime);
    for (Switch& s   : map.getSwitches())     s.update(deltaTime);
    for (spike& sp   : spikes)       sp.update(deltaTime);
    map.getPlayer().update(deltaTime);

    handleCollision(deltaTime);
    focusPlayer();

    map.updateRenderRect();
    for (ladder& l : ladders) l.updRenderRect(map.getCam());   // thang cũng theo camera
    for (Switch& s : map.getSwitches()) s.updRenderRect({ map.getCam().getX(), map.getCam().getY(), 0.0f, 0.0f });
    for (spike& sp : spikes) {
        sp.updRenderRect({ map.getCam().getX(), map.getCam().getY(), 0, 0 });
    }

}



void sceneMain::render(SDL_Renderer* renderer) {
    SDL_FRect bkgRect = { 0, 0, W, H };
    SDL_RenderTexture(renderer, map.getBkg(), nullptr, &bkgRect);

    for (platform& p : map.getPlatforms()) p.render(renderer);
    for (ladder& l : ladders) l.render(renderer);
    for (decor& d : map.getDecors()) d.render(renderer);
    for (enemy& e : map.getEnemies()) e.render(renderer);
    for (Switch& sw : map.getSwitches()) sw.render(renderer);
    for (spike& sp : spikes) sp.render(renderer);

    map.getPlayer().render(renderer);
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
    for (ladder& l : ladders) {
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

    //Xu li player cham cong tac
    for (Switch& sw : map.getSwitches()) {
        if (!sw.getIsActivated() && checkCollision(p, sw)) {
            sw.trigger();

            float switchCenterX = sw.getX() + sw.getWidth() / 2.0f;
            float switchCenterY = sw.getY() + sw.getHeight() / 2.0f;

            float radius = 400.0f;

            std::erase_if(spikes, [switchCenterX, switchCenterY, radius](const spike& sp) {
                float spikeCenterX = sp.getX() + sp.getWidth() / 2.0f;
                float spikeCenterY = sp.getY() + sp.getHeight() / 2.0f;

                float distance = std::hypot(switchCenterX - spikeCenterX, switchCenterY - spikeCenterY);

                return distance <= radius;
                });
        }
    }
    std::erase_if(spikes, [this, &p](const spike& sp) {
        if (checkCollision(p, sp)) {
            return true;
        }
        return false;
        });
}


void sceneMain::handleInput(const SDL_Event& event) {
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
                map.getPlayer().setMovingUp(true);
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