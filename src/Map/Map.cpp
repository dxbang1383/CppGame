#include "Map.h"

Map::Map() : mainPlayer(100.0, 100.0, 50.0, 50.0) {
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
    double ey = 50.0 + SDL_rand(250);
    enemies.emplace_back(ex, ey, 40.0, 40.0);
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
}