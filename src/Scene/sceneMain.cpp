#include "sceneMain.h"
// Constructor
sceneMain::sceneMain() {

}
// Map da tu dung san trong constructor cua no
// =========================================================
// LADDER
// =========================================================

// Cầu thang 1: nối platform ở row 25 -> row 21
    

    int ladderCol = 12;

    for (int row = 21; row <= 25; row++) {
        ladders.emplace_back(ladderCol, row);
    }

    // Cầu thang 2: nối khu vực giữa map
    ladderCol = 20;

    for (int row = 16; row <= 20; row++) {
        ladders.emplace_back(ladderCol, row);
    }

    // Cầu thang 3: khu vực cao
    ladderCol = 27;

    for (int row = 12; row <= 16; row++) {
        ladders.emplace_back(ladderCol, row);
    }
    ladderCol = 14;

    for (int row = 4; row <= 18; row++) {
        ladders.emplace_back(ladderCol, row);
    }

    // Cầu thang 4: gần cuối map
    ladderCol = 53;

    for (int row = 15; row <= 20; row++) {
        ladders.emplace_back(ladderCol, row);
    }


    // =========================================================
    // SWITCH
    // =========================================================

    // Switch 1: khu vực đầu map
    map.getSwitches().emplace_back(10, 20);

    // Switch 2: khu vực giữa map
    map.getSwitches().emplace_back(27, 11);

    // Switch 3: gần cuối map
    map.getSwitches().emplace_back(50, 19);


    // =========================================================
    // SPIKE
    // =========================================================

    // Bẫy 1: sau khu vực platform đầu
    for (int col = 11; col <= 13; col++) {
        spikes.emplace_back(col, 20);
    }

    // Bẫy 2: khu vực giữa map
    for (int col = 28; col <= 31; col++) {
        spikes.emplace_back(col, 20);
    }

    // Bẫy 3: khu vực cầu
    for (int col = 37; col <= 38; col++) {
        spikes.emplace_back(col, 20);
    }

    // Bẫy 4: gần cuối map
    for (int col = 46; col <= 49; col++) {
        spikes.emplace_back(col, 20);
    }

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
    // Thang
    SDL_Texture* ladTex = resourceManager::getTexture(renderer, "ladder");
    for (ladder& l : ladders) l.setTexture(ladTex);

    SDL_Texture* switchTex = resourceManager::getTexture(renderer, "switch");
    for (Switch& sw : map.getSwitches()) {
        sw.setTexture(switchTex);
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

    SDL_Texture* spikeTex = resourceManager::getTexture(renderer, "spike");
    for (spike& sp : spikes) {
        sp.setTexture(spikeTex);
    }

    SDL_Texture* boxCoin = resourceManager::getTexture(renderer, "box_coin");
    SDL_Texture* boxQuestion = resourceManager::getTexture(renderer, "box_question");
    SDL_Texture* boxItem = resourceManager::getTexture(renderer, "box_item");

    Icoin = resourceManager::getTexture(renderer, "i_coin");
    Istar = resourceManager::getTexture(renderer, "i_star");
    Ispeed = resourceManager::getTexture(renderer, "i_speed");
    Iheart = resourceManager::getTexture(renderer, "i_heart");
    Inogravity = resourceManager::getTexture(renderer, "i_nogravity");
    Idoublejump = resourceManager::getTexture(renderer, "i_doublejump");
    Ihighjump = resourceManager::getTexture(renderer, "i_highjump");

    for (itemBox& box : map.getBoxes()) {
        switch (box.getBoxType()) {

        case BoxType::COIN:
            box.setTexture(boxCoin);
            break;

        case BoxType::QUESTION:
            box.setTexture(boxQuestion);
            break;

        case BoxType::ITEM:
            box.setTexture(boxItem);
            break;
        }
    }

    for (Item& it : map.getItems()) {
        switch (it.getItemType()) {
        case ItemType::COIN1:
            it.setTexture(Icoin);
            break;
        case ItemType::STAR:
            it.setTexture(Istar);
            break;
        case ItemType::SPEED:
            it.setTexture(Ispeed);
            break;
        case ItemType::HEART:
            it.setTexture(Iheart);
            break;
        case ItemType::NO_GRAVITY:
            it.setTexture(Inogravity);
            break;
        case ItemType::DOUBLE_JUMP:
            it.setTexture(Idoublejump);
            break;
        case ItemType::HIGH_JUMP:
            it.setTexture(Ihighjump);
            break;
        }
    }
    /*map.getItems().clear();

    map.getItems().emplace_back(
        10 * platform::TILE_SIZE,
        10 * platform::TILE_SIZE,
        platform::TILE_SIZE,
        platform::TILE_SIZE,
        ItemType::COIN
    );
    if (Icoin != nullptr) {
        map.getItems().back().setTexture(Icoin);
    }
    map.getItems().back().updRenderRect(map.getCam());

    map.getItems().emplace_back(
        12 * platform::TILE_SIZE,
        10 * platform::TILE_SIZE,
        platform::TILE_SIZE,
        platform::TILE_SIZE,
        ItemType::STAR
    );
    if (Istar != nullptr) {
        map.getItems().back().setTexture(Istar);
    }
    map.getItems().back().updRenderRect(map.getCam());*/
}

void sceneMain::update(float deltaTime) {
    if (paused || lost) return;
    settings.close();

    for (platform& x : map.getPlatforms()) x.update(deltaTime);
    for (decor& d : map.getDecors())       d.update(deltaTime);
    for (flyer& f : map.getFlyers())       f.update(deltaTime);
    for (walker& w : map.getWalkers())     w.update(deltaTime);
    for (platform& x : map.getPlatforms())    x.update(deltaTime);
    for (decor& d    : map.getDecors())       d.update(deltaTime);
    for (enemy& e    : map.getEnemies())      e.update(deltaTime);
    for (Switch& s   : map.getSwitches())     s.update(deltaTime);
    for (spike& sp   : spikes)       sp.update(deltaTime);
 
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
    for (ladder& l : ladders) l.updRenderRect(map.getCam());   // thang cũng theo camera
    for (Switch& s : map.getSwitches()) s.updRenderRect(map.getCam());
    for (spike& sp : spikes) sp.updRenderRect(map.getCam());
    for (itemBox& box : map.getBoxes()) box.updRenderRect(map.getCam());
    for (Item& item : map.getItems()) item.updRenderRect(map.getCam());
}



void sceneMain::render(SDL_Renderer* renderer) {
    SDL_FRect bkgRect = { 0, 0, W, H };
    SDL_RenderTexture(renderer, map.getBkg(), nullptr, &bkgRect);

    for (platform& p : map.getPlatforms()) p.render(renderer);
    for (ladder& l : map.getLadders()) l.render(renderer);
    for (decor& d : map.getDecors()) d.render(renderer);
    for (flyer& f : map.getFlyers()) f.render(renderer);
    for (walker& w : map.getWalkers()) w.render(renderer);
    for (enemy& e : map.getEnemies()) e.render(renderer);
    for (Switch& sw : map.getSwitches()) sw.render(renderer);
    for (spike& sp : spikes) sp.render(renderer);
    for (itemBox& box : map.getBoxes()) box.render(renderer);
    for (Item& it : map.getItems()) it.render(renderer);
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

    // Player cung dau vao hop
    for (itemBox& box : map.getBoxes()) {

        bool horizontalOverlap =
            p.getX() < box.getX() + box.getWidth() &&
            p.getX() + p.getWidth() > box.getX();

        bool verticalOverlap =
            p.getY() < box.getY() + box.getHeight() &&
            p.getY() + p.getHeight() > box.getY();

        // Đang nhảy lên và chạm box
        if (p.getVelocityY() < 0 &&
            horizontalOverlap &&
            verticalOverlap)
        {
            // Đưa player xuống ngay dưới box
            p.setY(box.getY() + box.getHeight());

            // Không cho player tiếp tục bay lên
            p.setVelocityY(0);

            // Chỉ box chưa kích hoạt mới activate
            // Chỉ box chưa kích hoạt mới activate
            if (!box.isActivated()) {

                box.activate();
                ItemType itemType = ItemType::COIN1;

                if (box.getBoxType() == BoxType::COIN) {
                    
                    itemType = ItemType::COIN1;
                }
                else if (box.getBoxType() == BoxType::QUESTION) {
                   
                    static const ItemType questionPool[] = {
                        ItemType::HEART,
                        ItemType::SPEED,
                        ItemType::DOUBLE_JUMP
                    };
                    itemType = questionPool[rand() % 3];
                }
                else if (box.getBoxType() == BoxType::ITEM) {
                   
                    static const ItemType itemPool[] = {
                        ItemType::NO_GRAVITY,
                        ItemType::HIGH_JUMP,
                        ItemType::STAR,
                    
                    };
                    itemType = itemPool[rand() % 3];
                }

                Item newItem(
                    box.getRewardX() - 12.0,
                    box.getRewardY(),
                    24.0,
                    24.0,
                    itemType
                );

                switch (itemType) {

                case ItemType::COIN1:
                    newItem.setTexture(Icoin);
                    break;

                case ItemType::STAR:
                    newItem.setTexture(Istar);
                    break;

                case ItemType::DOUBLE_JUMP:
                    newItem.setTexture(Idoublejump);
                    break;

                case ItemType::NO_GRAVITY:
                    newItem.setTexture(Inogravity);
                    break;

                case ItemType::HIGH_JUMP:
                    newItem.setTexture(Ihighjump);
                    break;

                case ItemType::HEART:
                    newItem.setTexture(Iheart);
                    break;

                case ItemType::SPEED:
                    newItem.setTexture(Ispeed);
                    break;
                }

                newItem.setIVelocityY(-5.0);
                newItem.updRenderRect(map.getCam());

                map.getItems().push_back(newItem);
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
                    float spikeCenterX = sp.getX() +    sp.getWidth() / 2.0f;
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

        // Kiểm tra player nhặt item
        for (Item& item : map.getItems()) {
            if (!item.isCollected() && checkCollision(p, item)) {
                item.collect();
                p.collectItem(item.getItemType()); // Kích hoạt hiệu ứng cho player
            }
        }

        // Xóa các item đã bị nhặt khỏi map
        std::erase_if(map.getItems(), [](const Item& item) {
            return item.isCollected();
            });
    }
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
            // 1. Ưu tiên kiểm tra trạng thái Không trọng lực (No Gravity)
            if (map.getPlayer().isNoGravity()) {
                map.getPlayer().setMovingUp(true);
            }
            // 2. Nếu đang chạm thang thì leo lên
            else if (map.getPlayer().IsTouchingLadder()) {
                map.getPlayer().setIsClimbing(true);
                map.getPlayer().setOnGround(false);
                map.getPlayer().setMovingUp(true);
            }
            // 3. Bình thường thì nhảy
            else {
                map.getPlayer().jump();
            }
            break;

        case SDLK_S:
        case SDLK_DOWN:
            // 1. Kiểm tra trạng thái Không trọng lực
            if (map.getPlayer().isNoGravity()) {
                map.getPlayer().setMovingDown(true);
            }
            // 2. Nếu đang chạm thang thì leo xuống
            else if (map.getPlayer().IsTouchingLadder()) {
                map.getPlayer().setIsClimbing(true);
                map.getPlayer().setMovingDown(true);
                map.getPlayer().setMovingDown(true); // Đã sửa lỗi cũ (trước đó bạn để setMovingUp)
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

        case SDLK_SPACE:
        case SDLK_W:
        case SDLK_UP:
            map.getPlayer().setMovingUp(false); // Thả phím W/UP -> Dừng bay lên / Dừng leo
            break;

        case SDLK_S:
        case SDLK_DOWN:
            map.getPlayer().setMovingDown(false); // Thả phím S/DOWN -> Dừng bay xuống / Dừng leo
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