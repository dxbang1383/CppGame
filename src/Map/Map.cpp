#include "Map.h"

Map::Map() : mainPlayer(100.0, 100.0, 50.0, 50.0) {

    // =========================================================
    // GROUND - NỀN MAP
    // Map rộng 60 ô
    // =========================================================

    for (int x = 0; x < 60; x++) {
        plat.emplace_back(x, 29, "map1", 2, 4);
    }


    // =========================================================
    // KHU VỰC 1 - BÊN TRÁI
    // =========================================================

    for (int x = 2; x <= 8; x++) {
        plat.emplace_back(x, 25, "map1", 2, 4);
    }

    for (int x = 4; x <= 10; x++) {
        plat.emplace_back(x, 21, "map1", 2, 4);
    }

    for (int x = 7; x <= 13; x++) {
        plat.emplace_back(x, 17, "map1", 2, 4);
    }


    // =========================================================
    // KHU VỰC 2 - CẦU THANG
    // =========================================================

    plat.emplace_back(14, 24, "map1", 2, 4);
    plat.emplace_back(15, 23, "map1", 2, 4);
    plat.emplace_back(16, 22, "map1", 2, 4);
    plat.emplace_back(17, 21, "map1", 2, 4);
    plat.emplace_back(18, 20, "map1", 2, 4);


    // =========================================================
    // KHU VỰC 3 - PLATFORM DÀI
    // =========================================================

    for (int x = 18; x <= 27; x++) {
        plat.emplace_back(x, 20, "map1", 2, 4);
    }

    for (int x = 21; x <= 25; x++) {
        plat.emplace_back(x, 16, "map1", 2, 4);
    }

    for (int x = 25; x <= 31; x++) {
        plat.emplace_back(x, 12, "map1", 2, 4);
    }


    // =========================================================
    // KHU VỰC 4 - HỐ VÀ CẦU
    // =========================================================

    for (int x = 32; x <= 36; x++) {
        plat.emplace_back(x, 20, "map1", 2, 4);
    }

    for (int x = 39; x <= 45; x++) {
        plat.emplace_back(x, 20, "map1", 2, 4);
    }

    // Cầu phía trên
    for (int x = 34; x <= 40; x++) {
        plat.emplace_back(x, 15, "map1", 2, 4);
    }


    // =========================================================
    // KHU VỰC 5 - PLATFORM CAO
    // =========================================================

    for (int x = 42; x <= 49; x++) {
        plat.emplace_back(x, 15, "map1", 2, 4);
    }

    for (int x = 46; x <= 53; x++) {
        plat.emplace_back(x, 10, "map1", 2, 4);
    }


    // =========================================================
    // KHU VỰC 6 - ĐƯỜNG ĐI CUỐI MAP
    // =========================================================

    for (int x = 50; x <= 58; x++) {
        plat.emplace_back(x, 20, "map1", 2, 4);
    }

    for (int x = 54; x <= 59; x++) {
        plat.emplace_back(x, 16, "map1", 2, 4);
    }

    for (int x = 57; x <= 59; x++) {
        plat.emplace_back(x, 12, "map1", 2, 4);
    }


    // =========================================================
    // DECOR
    // =========================================================

    decorList.emplace_back(
        10, 16,
        "map1",
        11, 7,
        "x++"
    );

    decorList.emplace_back(
        28, 11,
        "map1",
        11, 7,
        "x++"
    );

    decorList.emplace_back(
        45, 14,
        "map1",
        11, 7,
        "x++"
    );


    // =========================================================
    // ENEMY
    // =========================================================

    SDL_srand(0);

    enemies.emplace_back(
        500.0,
        500.0,
        40.0,
        40.0
    );

    enemies.emplace_back(
        900.0,
        350.0,
        40.0,
        40.0
    );

    enemies.emplace_back(
        1400.0,
        450.0,
        40.0,
        40.0
    );

    enemies.emplace_back(
        1900.0,
        300.0,
        40.0,
        40.0
    );

    enemies.emplace_back(
        2400.0,
        450.0,
        40.0,
        40.0
    ); 
    boxes.emplace_back(
        15 * platform::TILE_SIZE,
        25 * platform::TILE_SIZE,
        platform::TILE_SIZE,
        platform::TILE_SIZE,
        BoxType::COIN
    );

    boxes.emplace_back(
        20 * platform::TILE_SIZE,
        25 * platform::TILE_SIZE,
        platform::TILE_SIZE,
        platform::TILE_SIZE,
        BoxType::QUESTION
    );

    boxes.emplace_back(
        28 * platform::TILE_SIZE,
        25 * platform::TILE_SIZE,
        platform::TILE_SIZE,
        platform::TILE_SIZE,
        BoxType::ITEM
    );
    boxes.emplace_back(
        26 * platform::TILE_SIZE,
        11 * platform::TILE_SIZE,
        platform::TILE_SIZE,
        platform::TILE_SIZE,
        BoxType::QUESTION
    );
    items.emplace_back(
        10 * platform::TILE_SIZE,
        10 * platform::TILE_SIZE,
        platform::TILE_SIZE,
        platform::TILE_SIZE,
        ItemType::COIN1
    );

   items.emplace_back(
        12 * platform::TILE_SIZE,
        10 * platform::TILE_SIZE,
        platform::TILE_SIZE,
        platform::TILE_SIZE,
        ItemType::NO_GRAVITY
    );
   items.emplace_back(
       16 * platform::TILE_SIZE,
       10 * platform::TILE_SIZE,
       platform::TILE_SIZE,
       platform::TILE_SIZE,
       ItemType::HIGH_JUMP
   );
}

void Map::clear() {
    plat.clear();
    decorList.clear();
    enemies.clear();

    cols = rows = 0;

    startCol = 0;
    startRow = 0;
    goalCol = 0;
    goalRow = 0;
    dirty = false;
}

void Map::addTextures(SDL_Renderer* renderer) {
    rend = renderer; // tam thoi
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

/// <summary>
/// Xóa tile trên cùng của map
/// </summary>
/// <param name="col"></param> 
/// <param name="row"></param>
/// <param name="layer"></param> p , e, d
/// <returns></returns>
bool Map::eraseAt(int col, int row, char layer) {
    // platform 
    if (layer == 'P') {
        for (int i = (int)plat.size() - 1; i >= 0; i--) {
            platform& p = plat[i];

            int pCol = (int)(p.getX() / platform::TILE_SIZE);
            int pRow = (int)(p.getY() / platform::TILE_SIZE);

            if (pCol == col && pRow == row) {
                plat.erase(plat.begin() + i);
                dirty = true;
                return true;
            }
        }
    }
    // decor
    else if (layer == 'D') {
        for (int i = (int)decorList.size() - 1; i >= 0; i--) {
            decor& d = decorList[i];

            int dCol = (int)(d.getX() / platform::TILE_SIZE);
            int dRow = (int)(d.getY() / platform::TILE_SIZE);

            if (dCol == col && dRow == row) {
                decorList.erase(decorList.begin() + i);
                dirty = true;
                return true;
            }
        }
    }
    return false;
}

void Map::addPlatform(int col, int row, const std::string& texKey, int srcX, int srcY) {
    // to do
}

void Map::addDecor(int col, int row, const std::string& texKey, int srcX, int srcY) {
    // to do
}

void Map::addEnemy(int col, int row, const std::string& texKey, int srcX, int srcY) {
    // to do
}

bool Map::load(const std::string& path) {
    return true;
}

bool Map::save(const std::string& path) {
    return true;
}

void Map::updateRenderRect() {
    mainPlayer.updRenderRect(cam);
    for (platform& x : plat) x.updRenderRect(cam);
    for (decor& d : decorList) d.updRenderRect(cam);
    for (enemy& e : enemies) e.updRenderRect(cam);
    for (itemBox& box : boxes) box.updRenderRect(cam);
    for (Item& it : items) it.updRenderRect(cam);
    for (Switch& sw : switches) sw.updRenderRect(cam);
}