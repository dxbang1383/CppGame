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
    ladderCol = 14;

    for (int row = 4; row <= 18; row++) {
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
    for (itemBox& box : map.getBoxes()) {
        box.updRenderRect({ map.getCam().getX(), map.getCam().getY(), 0, 0 });
    }
    for (Item& item : map.getItems()) {
        item.updRenderRect({ map.getCam().getX(), map.getCam().getY(), 0, 0 });
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
    for (itemBox& box : map.getBoxes()) box.render(renderer);
    for (Item& it : map.getItems()) it.render(renderer);
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
            // 1. Ưu tiên kiểm tra trạng thái Không trọng lực (No Gravity)
            if (map.getPlayer().isNoGravity()) {
                map.getPlayer().setMovingUp(true);
            }
            // 2. Nếu đang chạm thang thì leo lên
            else if (map.getPlayer().IsTouchingLadder()) {
                map.getPlayer().setIsClimbing(true);
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
                map.getPlayer().setMovingDown(true); // Đã sửa lỗi cũ (trước đó bạn để setMovingUp)
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