#include "sceneMain.h"
#include "../engine/soundManager.h"

// Constructor
sceneMain::sceneMain() {
// Toan bo man choi (dia hinh, thang, quai, switch, spike) nap tu level2.txt
}

void sceneMain::preLoad(SDL_Renderer* renderer) {
    gameRenderer = renderer;
    map.addTextures(renderer); // bkg, platform, decor, enemy, player

    mapPath = std::string(PROJECT_SOURCE_DIR) + "/assets/maps/level2.txt";
    if (!map.load(mapPath)) {
        SDL_Log("Khong nap duoc map: %s -> dung map mac dinh", mapPath.c_str());
    }
    // animation cho goal 
    goalFlag.setTexture(resourceManager::getTexture(renderer, "flag"));

    renderGoalFlag(renderer);

    pauseMenu.preLoad(renderer);
    gameOverMenu.preLoad(renderer);
    settings.preLoad(renderer);

    iconTex = resourceManager::getTexture(renderer, "menu");

    Icoin = resourceManager::getTexture(renderer, "i_coin");
    Istar = resourceManager::getTexture(renderer, "i_star");
    Ispeed = resourceManager::getTexture(renderer, "i_speed");
    Iheart = resourceManager::getTexture(renderer, "i_heart");
    Inogravity = resourceManager::getTexture(renderer, "i_nogravity");
    Idoublejump = resourceManager::getTexture(renderer, "i_doublejump");
    Ihighjump = resourceManager::getTexture(renderer, "i_highjump");
    NDiamonds = resourceManager::getTexture(renderer, "diamond");

}

void sceneMain::resetGame() {
    std::string mapPath = std::string(PROJECT_SOURCE_DIR) + "/assets/maps/level2.txt";
    if (!map.load(mapPath)) {
        SDL_Log("Khong nap duoc map: %s -> dung map mac dinh", mapPath.c_str());
    }
    resetPlayer();
}

void sceneMain::resetPlayer() {
    player& p = map.getPlayer();

    p.setHealth(3);
    p.clearHurt();
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

// Nap lai ca man choi. map.load() tu dat lai vi tri player ve o start,
// player.reset() xoa het item/mau/toc do, con clearHurt() xoa mien thuong
void sceneMain::resetLevel() {
    map.load(mapPath);
    map.addTextures(gameRenderer);
    map.getPlayer().reset();
    map.getPlayer().clearHurt();
    lost = false;
    paused = false;
    complete = false;
    loseSoundPending = false;
}

// het mau hoac roi xuong vuc.
// Cham bay/quai chi tru mau qua takeDamage(), khong goi thang vao day
void sceneMain::playerDies(bool byTrap) {
    if (lost) return;
    lost = true;
    if (byTrap) soundManager::playEffect("punji");
    loseTimer = 2.0f;
    loseSoundPending = true;
}

void sceneMain::update(float deltaTime) {
    if (loseSoundPending) {
        loseTimer -= deltaTime;
        if (loseTimer <= 0.0f) {
            soundManager::playEffect("lose");
            loseSoundPending = false;
        }
    }

    if (paused || lost) return;
    settings.close();

    for (platform& x : map.getPlatforms()) x.update(deltaTime);
    for (decor& d : map.getDecors())       d.update(deltaTime);
    for (flyer& f : map.getFlyers())       f.update(deltaTime);
    for (walker& w : map.getWalkers())     w.update(deltaTime);
    for (Switch& s : map.getSwitches())    s.update(deltaTime);
    for (spike& sp : map.getSpikes())      sp.update(deltaTime);
    for (Item& i : map.getItems())         i.update(deltaTime);
    for (itemBox& b : map.getBoxes())      b.update(deltaTime);
    for (Coin& c : map.getCoins())         c.update(deltaTime);
    for (Diamond& dia : map.getDiamond())    dia.update(deltaTime);


    map.getPlayer().update(deltaTime);
    goalFlag.update(deltaTime);

    // xóa phần box rơi ra ngoài map
    std::erase_if(map.getBoxes(), [this](const itemBox& b) {
        return b.getY() > deathY;
        });

    handleCollision(deltaTime);
    checkCollectables();

    {
        player& pl = map.getPlayer();
        if (pl.getIsClimbing() && pl.getVelocityY() != 0.0) {
            ladderSoundTimer -= deltaTime;
            if (ladderSoundTimer <= 0.0f) {
                soundManager::playEffect("ladder");
                ladderSoundTimer = 0.3f;
            }
        }
        else {
            ladderSoundTimer = 0.0f;
        }
    }

    focusPlayer();

    map.updateRenderRect();

    // Roi xuong vuc: chet ngay, khong tru mau
    if (map.getPlayer().getY() > deathY) playerDies();

    checkEnd();
}

void sceneMain::render(SDL_Renderer* renderer) {
    SDL_FRect bkgRect = { 0, 0, W, H };
    SDL_RenderTexture(renderer, map.getBkg(), nullptr, &bkgRect);

    for (platform& p : map.getPlatforms()) p.render(renderer);
    for (ladder& l : map.getLadders()) l.render(renderer);
    for (decor& d : map.getDecors()) d.render(renderer);
    for (flyer& f : map.getFlyers()) f.render(renderer);
    for (walker& w : map.getWalkers()) w.render(renderer);
    for (Switch& sw : map.getSwitches()) sw.render(renderer);
    for (spike& sp : map.getSpikes()) sp.render(renderer);
    for (itemBox& box : map.getBoxes()) box.render(renderer);
    for (Item& it : map.getItems()) it.render(renderer);
    for (Coin& c : map.getCoins()) { c.render(renderer); }
    for (Diamond& dia : map.getDiamond()) { dia.render(renderer); }
    for (teleport& t : map.getTeleports()) t.render(renderer);

    renderGoalFlag(renderer);

    map.getPlayer().render(renderer);


    renderHUD(renderer);
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

void sceneMain::handlePlatformCollision(float deltaTime) {
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

    // Cap nhat lai trang thai dung tren mat dat cho player
    p.setOnGround(onAnyGround);
}

void sceneMain::handleItemBoxCollision(float deltaTime) {
    player& p = map.getPlayer();

    // Player cung dau vao hop
    for (itemBox& box : map.getBoxes()) {

        bool horizontalOverlap =
            p.getX() < box.getX() + box.getWidth() &&
            p.getX() + p.getWidth() > box.getX();

        bool verticalOverlap =
            p.getY() < box.getY() + box.getHeight() &&
            p.getY() + p.getHeight() > box.getY();

        if (p.getVelocityY() < 0 &&
            horizontalOverlap &&
            verticalOverlap && 
            !box.isActivated())
        {
            // Đưa player xuống ngay dưới box
            p.setY(box.getY() + box.getHeight());

            // Không cho player tiếp tục bay lên
            p.setVelocityY(0);

            // Chỉ box chưa kích hoạt mới activate
            if (!box.isActivated()) {

                box.activate();
                soundManager::playEffect("itembox");
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
    }
}

void sceneMain::handleLadderCollision(float deltaTime) {
    player& p = map.getPlayer();

    // Biến này để kiểm tra xem player có đang chạm với ladder nào không 
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
}

void sceneMain::handleSwitchCollision(float deltaTime) {
    player& p = map.getPlayer();
    // Xu li player cham cong tac
    for (Switch& sw : map.getSwitches()) {
        if (!sw.getIsActivated() && checkCollision(p, sw)) {
            sw.trigger();
            soundManager::playEffect("switch");

            float switchCenterX = sw.getX() + sw.getWidth() / 2.0f;
            float switchCenterY = sw.getY() + sw.getHeight() / 2.0f;

            float radius = 400.0f;

            std::erase_if(map.getSpikes(), [switchCenterX, switchCenterY, radius](const spike& sp) {
                float spikeCenterX = sp.getX() + sp.getWidth() / 2.0f;
                float spikeCenterY = sp.getY() + sp.getHeight() / 2.0f;

                float distance = std::hypot(switchCenterX - spikeCenterX, switchCenterY - spikeCenterY);

                return distance <= radius;
                });
        }
    }
}

void sceneMain::handleSpikeCollison(float deltaTime) {
    player& p = map.getPlayer();

    // Cham spike: tru 1 mau + tieng punji. takeDamage() tu lo phan mien thuong,
    // het mau thi checkEnd() moi goi playerDies()
    for (spike& sp : map.getSpikes()) {
        if (sp.isActive() && checkCollision(p, sp)) {
            if (p.takeDamage()) {
                soundManager::playEffect("punji");
                p.setVelocityY(-350);   // bat lui len
            }
            break;
        }
    }
}

void sceneMain::handleItemCollison(float deltaTime) {
    player& p = map.getPlayer();
    // Kiểm tra player nhặt item
    for (Item& item : map.getItems()) {
        if (!item.isCollected() && checkCollision(p, item)) {
            item.collect();
            p.collectItem(item.getItemType());
            if (item.getItemType() == ItemType::COIN1) soundManager::playEffect("earncoin");
            else soundManager::playEffect("item");
        }
    }

    // Xóa các item đã bị nhặt khỏi map
    std::erase_if(map.getItems(), [](const Item& item) {
        return item.isCollected();
        });
}

void sceneMain::handleEnemyCollision(float deltaTime) {
    player& p = map.getPlayer();
    float px = p.getX(), py = p.getY(), pw = p.getWidth(), ph = p.getHeight();

    for (walker& w : map.getWalkers()) {
        
        // 4 tham số này bo quanh enemy
        float wx = w.getX() + w.getInsetSide();
        float wy = w.getY() + w.getInsetTop();
        float ww = w.getWidth() - 2 * w.getInsetSide();
        float wh = w.getHeight() - w.getInsetTop();

        // nếu có va chạm với player
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
        // kind 1 đầu đinh
        if (k == 1) {
            bool wasStopped = w.isStopped();
            w.stop();
            // giam len dau dinh -> mat mau; huc ben hong -> ha duoc quai
            if (side == 2) {
                if (p.takeDamage()) {
                    soundManager::playEffect("punji");
                    p.setVelocityY(-350);
                }
            }
            else if (!wasStopped) soundManager::playEffect("enemy");
        }
        // kind 2 quái nhỏ
        else if (k == 2) {
            bool wasStopped = w.isStopped();
            w.stop();
            // cham ben hong -> mat mau; giam len dau -> ha duoc quai
            if (side != 2) {
                if (p.takeDamage()) {
                    soundManager::playEffect("punji");
                    p.setVelocityY(-350);
                }
            }
            else if (!wasStopped) soundManager::playEffect("enemy");
        }
        // kind 3 quái lớn 
        else if (k == 3) {
            if (side == 2 && !w.isStopped()) {
                w.stop();
                soundManager::playEffect("enemy");
            }
        }
    }

    px = p.getX(); py = p.getY();

    for (flyer& f : map.getFlyers()) {
        if (!f.isAlive()) continue;// còn sồngs
        if (!checkCollision(p, f)) continue; // va chạm 

        f.kill(); // alive = false
        soundManager::playEffect("enemy");

        // dang mien thuong thi takeDamage() tra false -> quai van chet, player khong mat mau
        if (p.takeDamage()) {
            soundManager::playEffect("punji");
            p.setVelocityY(-350);
        }
    }
    std::erase_if(map.getFlyers(), [](const flyer& f) { return !f.isAlive(); });
}

// tâm của người chơi đang ở ô nào 
bool sceneMain::playerAtCell(int col, int row) {
    player& p = map.getPlayer();
    int pc = (int)((p.getX() + p.getWidth()  / 2) / tile::TILE_SIZE);
    int pr = (int)((p.getY() + p.getHeight() / 2) / tile::TILE_SIZE);
    return pc == col && pr == row;
}

void sceneMain::movePlayerToCell(int col, int row) {
    player& p = map.getPlayer();
    p.setX(col * tile::TILE_SIZE);
    p.setY(row * tile::TILE_SIZE - tile::TILE_SIZE / 2);
    p.setVelocityY(-100);
    p.setOnGround(false);
    teleportCooldown = 0.5f;
    soundManager::playEffect("click");
}

void sceneMain::handleTeleportCollision(float deltaTime) {
    if (teleportCooldown > 0.0f) {
        teleportCooldown -= deltaTime;
        return;
    }

    player& p = map.getPlayer();

    if (!p.getIsMovingDown()) return;

    for (teleport& t : map.getTeleports()) {
        if (!playerAtCell(t.getCol(), t.getRow())) continue;
        teleport* dest = map.findPartner(t);

        if (dest == nullptr) {
            continue; // tele lỗi chỉ có 1 cổng
            std::cout << "cong nay loi chi co 1 port" << std::endl;
        }

        movePlayerToCell(dest->getCol(), dest->getRow());
        break;
    }
}

void sceneMain::handleCollision(float deltaTime) {

    // Va chạm player và platform 
    handlePlatformCollision(deltaTime);
    // Va chạm player và ItemBox
    handleItemBoxCollision(deltaTime);
    // Va chạm player và ItemBox
    handleLadderCollision(deltaTime);
    // Va chạm switch và player 
    handleSwitchCollision(deltaTime);
    // Cham spike -> thua, tru khi dang bat bien nho STAR
    handleSpikeCollison(deltaTime);
    // Va chạm item với player 
    handleItemCollison(deltaTime);
    // Va chạm enemy với player 
    handleEnemyCollision(deltaTime);
    // tele khi có moving down và có gần 1 cổng 
    handleTeleportCollision(deltaTime);
}

void sceneMain::handleInput(const SDL_Event& event) {
    if (handleSettingsInput(event))  return;
    if (handleGameOverInput(event))  return;
    if (handlePauseToggle(event))    return;
    if (handlePauseMenuInput(event)) return;

    handlePlayerInput(event);
}

// nút bánh răng 
bool sceneMain::handleSettingsInput(const SDL_Event& event) {
    if (!paused && !lost) return false; // đang chơi game thì tiếp 
    if (event.type != SDL_EVENT_MOUSE_BUTTON_DOWN) return false; // tạm thời chỉ nhận input chuột trái
    if (event.button.button != SDL_BUTTON_LEFT) return false;

    int base = lost ? 0 : 1;
    float sx = 1220.0f - base * 50.0f;
    return settings.handleClick(event.button.x, event.button.y, sx, 20.0f);
}

// Khi thua, menu game over nuot toan bo input
bool sceneMain::handleGameOverInput(const SDL_Event& event) {
    if (!lost) return false;

    if (event.type == SDL_EVENT_MOUSE_MOTION) {
        gameOverMenu.handleMouseMove(event.motion.x, event.motion.y);
    }
    else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN
             && event.button.button == SDL_BUTTON_LEFT) {
        gameOverMenu.handleClick(event.button.x, event.button.y);
        int a = gameOverMenu.getAction();
        if (a == GAMEOVER_REPLAY)     { resetLevel(); lost = false; }
        else if (a == GAMEOVER_MODE2) { resetLevel(); lost = false; sceneAction = SCENE_EDITOR; }
        else if (a == GAMEOVER_MENU)  { resetLevel(); lost = false; sceneAction = SCENE_MENU; }
        else if (a == GAMEOVER_QUIT)  { sceneAction = SCENE_QUIT; }
        gameOverMenu.resetAction();
    }
    return true;
}

// Hai duong bat/tat tam dung: bam icon hoac phim P
bool sceneMain::handlePauseToggle(const SDL_Event& event) {
    bool clickIcon =
        event.type == SDL_EVENT_MOUSE_BUTTON_DOWN
        && event.button.button == SDL_BUTTON_LEFT
        && event.button.x >= toggleBtnRect.x && event.button.x <= toggleBtnRect.x + toggleBtnRect.w
        && event.button.y >= toggleBtnRect.y && event.button.y <= toggleBtnRect.y + toggleBtnRect.h;

    bool pressP = event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_P;

    if (!clickIcon && !pressP) return false;

    paused = !paused;
    pauseMenu.resetAction();
    return true;
}

// Khi tam dung, menu pause nuot toan bo input
bool sceneMain::handlePauseMenuInput(const SDL_Event& event) {
    if (!paused) return false;

    if (event.type == SDL_EVENT_MOUSE_MOTION) {
        pauseMenu.handleMouseMove(event.motion.x, event.motion.y);
    }
    else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN
             && event.button.button == SDL_BUTTON_LEFT) {
        pauseMenu.handleClick(event.button.x, event.button.y);
        int a = pauseMenu.getAction();
        if (a == PAUSE_RESUME)      paused = false;
        else if (a == PAUSE_REPLAY) { resetLevel(); paused = false; }
        else if (a == PAUSE_MENU)   { resetLevel(); sceneAction = SCENE_MENU; paused = false; }
        else if (a == PAUSE_QUIT)   sceneAction = SCENE_QUIT;
        pauseMenu.resetAction();
    }
    return true;
}

void sceneMain::handlePlayerInput(const SDL_Event& event) {
    if (event.type == SDL_EVENT_KEY_DOWN)    handlePlayerKeyDown(event.key.key);
    else if (event.type == SDL_EVENT_KEY_UP) handlePlayerKeyUp(event.key.key);
}

void sceneMain::handlePlayerKeyDown(SDL_Keycode key) {
    player& p = map.getPlayer();

    switch (key) {
    case SDLK_A:
    case SDLK_LEFT:
        p.setDirection(-1);
        p.setMovingLeft(true);
        break;

    case SDLK_D:
    case SDLK_RIGHT:
        p.setMovingRight(true);
        p.setDirection(1);
        break;

    case SDLK_SPACE:
    case SDLK_W:
    case SDLK_UP:
        // 1. Ưu tiên kiểm tra trạng thái Không trọng lực (No Gravity)
        if (p.isNoGravity()) {
            p.setMovingUp(true);
        }
        // 2. Nếu đang chạm thang thì leo lên
        else if (p.IsTouchingLadder()) {
            p.setIsClimbing(true);
            p.setOnGround(false);
            p.setMovingUp(true);
        }
        // 3. Bình thường thì nhảy
        else {
            // chỉ kêu khi thực sự nhảy
            if (p.isOnGround() || p.canDoubleJump()) soundManager::playEffect("jump");
            p.jump();
        }
        break;

    case SDLK_S:
    case SDLK_DOWN:
        p.setMovingDown(true);

        // đang chạm vào thang thì set thành đang trèo
        if (!p.isNoGravity() && p.IsTouchingLadder()) {
            p.setIsClimbing(true);
        }
        break;

    case SDLK_L:
        map.load(std::string(PROJECT_SOURCE_DIR) + "/assets/maps/level1.txt");
        std::cout << "load " << std::endl;
        break;
    }
}

void sceneMain::handlePlayerKeyUp(SDL_Keycode key) {
    player& p = map.getPlayer();

    switch (key) {
    case SDLK_A:
    case SDLK_LEFT:
        p.setMovingLeft(false);
        break;

    case SDLK_D:
    case SDLK_RIGHT:
        p.setMovingRight(false);
        break;

    case SDLK_SPACE:
    case SDLK_W:
    case SDLK_UP:
        p.setMovingUp(false);
        break;

    case SDLK_S:
    case SDLK_DOWN:
        p.setMovingDown(false);
        break;
    }
}

void sceneMain::focusPlayer() {
    map.getCam().focus(map.getPlayer().getX(), map.getPlayer().getY(), W, H);
}

void sceneMain::switchScene() {
    //sau nay khoi tao nhan sk ban phim 
}

void sceneMain::checkCollectables() {
    player& p = map.getPlayer();

    // 1. Kiểm tra ăn Coin
    for (Coin& c : map.getCoins()) {
        if (!c.isCollected() && checkCollision(p, c)) {
            c.setCollected(true);
            p.addCoins(c.getValue());
        }
    }

    // 2. Kiểm tra ăn Kim Cương (Diamond)   
    for (Diamond& dia : map.getDiamond()) {
        if (!dia.isCollected() && checkCollision(p, dia)) {
            dia.setCollected(true);
            p.addDiamond();
        }
    }
    std::erase_if(map.getCoins(), [](const Coin& c) {
        return c.isCollected();
    });

    std::erase_if(map.getDiamond(), [](const Diamond& dia) {
        return dia.isCollected();
    });
}

void sceneMain::renderHUD(SDL_Renderer* renderer) {
    player& p = map.getPlayer();

    // 1. Vẽ khung nền bảng HUD
    SDL_FRect bgRect = { 20.0f, 20.0f, 180.0f, 160.0f };
    SDL_SetRenderDrawColor(renderer, 220, 220, 220, 255); // Màu xám sáng
    SDL_RenderFillRect(renderer, &bgRect);

    // Vẽ viền xám đậm xung quanh khung
    SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
    SDL_RenderRect(renderer, &bgRect);

    // Chuẩn bị màu chữ đen
    SDL_Color textColor = { 0, 0, 0, 255 };

    
    float scale = 0.42f;

    // 2. Dòng 1: COIN (: X)
    SDL_FRect coinIconRect = { 35.0f, 35.0f, 32.0f, 32.0f };
    SDL_RenderTexture(renderer, Icoin, nullptr, &coinIconRect);
    Text::draw(renderer, ": " + std::to_string(p.getCoins()),
               75.0f, 38.0f, textColor, scale);

    // 3. Dòng 2: HEART (: X)
    SDL_FRect heartIconRect = { 35.0f, 80.0f, 32.0f, 32.0f };
    SDL_RenderTexture(renderer, Iheart, nullptr, &heartIconRect);
    Text::draw(renderer, ": " + std::to_string(p.getHealth()),
               75.0f, 83.0f, textColor, scale);

    // 4. Dòng 3: DIAMOND 
    SDL_FRect diamondIconRect = { 35.0f, 125.0f, 32.0f, 32.0f };
    SDL_RenderTexture(renderer, NDiamonds, nullptr, &diamondIconRect);
    Text::draw(renderer, ": " + std::to_string(p.getDiamonds()),
        75.0f, 128.0f, textColor, scale);
}

void sceneMain::checkEnd() {
    // Het mau -> chet. Di qua playerDies() de tieng "lose" cung phat tre 2s
    // giong luc roi vuc, va khong bi phat lai moi frame
    if (map.getPlayer().getHealth() <= 0) playerDies();

    if (playerAtCell(map.getGoalCol(), map.getGoalRow())) {
        complete = true;
        lost = true; // chưa làm phần complete nên tamj như là lost
        soundManager::playEffect("win");
    }
}

void sceneMain::renderGoalFlag(SDL_Renderer* renderer) {
    if (!map.getHasGoal()) return;

    SDL_Texture* tex = goalFlag.getTexture();
    if (tex == nullptr) return;

    camera& cam = map.getCam();

    SDL_FRect dst;
    dst.x = SDL_roundf(cam.xWorldToScreen(map.getGoalCol() * tile::TILE_SIZE));
    dst.y = SDL_roundf(cam.yWorldToScreen(map.getGoalRow() * tile::TILE_SIZE));
    dst.w = tile::TILE_SIZE * cam.getScale();
    dst.h = tile::TILE_SIZE * cam.getScale();

    SDL_FRect src = goalFlag.getSrcRect();
    SDL_RenderTexture(renderer, tex, &src, &dst);
}
