#include "sceneMain.h"
#include "../engine/soundManager.h"

// Constructor
sceneMain::sceneMain() {
// Toan bo man choi (dia hinh, thang, quai, switch, spike) nap tu level2.txt
}

// Destruction 
sceneMain::~sceneMain() {
                
}

void sceneMain::preLoad(SDL_Renderer* renderer) {
    map.addTextures(renderer); // bkg, platform, decor, enemy, player

    std::string mapPath = std::string(PROJECT_SOURCE_DIR) + "/assets/maps/level2.txt";
    if (!map.load(mapPath)) {
        SDL_Log("Khong nap duoc map: %s -> dung map mac dinh", mapPath.c_str());
    }

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
    for (Switch& s : map.getSwitches())    s.update(deltaTime);
    for (spike& sp : map.getSpikes())      sp.update(deltaTime);
    for (Item& i : map.getItems())         i.update(deltaTime);
    for (itemBox& b : map.getBoxes())      b.update(deltaTime);
    map.getPlayer().update(deltaTime);

    // xóa phần box rơi ra ngoài map
    std::erase_if(map.getBoxes(), [this](const itemBox& b) {
        return b.getY() > deathY;
        });

    handleCollision(deltaTime);
    focusPlayer();

    map.updateRenderRect();

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
    for (Switch& sw : map.getSwitches()) sw.render(renderer);
    for (spike& sp : map.getSpikes()) sp.render(renderer);
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

    // Cham spike -> thua, tru khi dang bat bien nho STAR
    if (!p.isInvincible()) {
        for (spike& sp : map.getSpikes()) {
            if (sp.isActive() && checkCollision(p, sp)) {
                lost = true;
                soundManager::playEffect("lose");
                break;
            }
        }
    }
}

void sceneMain::handleItemCollison(float deltaTime) {
    player& p = map.getPlayer();
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

void sceneMain::handleEnemyCollision(float deltaTime) {
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
}

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