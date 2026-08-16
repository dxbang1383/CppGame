#include "Map.h"

Map::Map() : mainPlayer(100.0, 100.0, 50.0, 50.0) {
    // Map rong, moi noi dung deu den tu load()
}

void Map::clear() {
    plat.clear();
    decorList.clear();
    flyers.clear();
    walkers.clear();

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

    for (flyer& f : flyers)
        f.setTexture(resourceManager::getTexture(renderer, f.getType()));

    for (walker& w : walkers)
        w.setTexture(resourceManager::getTexture(renderer, w.getType()));
}

/// <summary>
/// Xóa tile trên cùng của map
/// </summary>
/// <param name="col"></param> 
/// <param name="row"></param>
/// <param name="layer"></param> p , e, d
/// <returns> true nếu xóa được một cái gì đó </returns>
bool Map::eraseAt(int col, int row, TileLayer layer ) {
    // platform 
    if (layer == TileLayer::LAYER_PLATFORM 
        || layer == TileLayer::LAYER_PLATFORM_XPP
        || layer == TileLayer::LAYER_PLATFORM_YPP) {
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
    else if (layer == TileLayer::LAYER_DECOR
            || layer == TileLayer::LAYER_DECOR_XPP
            || layer == TileLayer::LAYER_DECOR_YPP) {
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

void Map::addPlatform(int col, int row, std::string texKey,
                        int srcX, int srcY, std::string animType) {
    getPlatforms().emplace_back(col, row, texKey, srcX, srcY, animType);
    getPlatforms().back().setTexture(resourceManager::getTexture(rend, texKey));
    dirty = true;
}

void Map::addDecor(int col, int row, std::string texKey, 
                        int srcX, int srcY, std::string animType) {
    getDecors().emplace_back(col, row, texKey, srcX, srcY, animType);
    getDecors().back().setTexture(resourceManager::getTexture(rend, texKey));
    dirty = true;
}

void Map::addFlyer(int col, int row, int patrol) {
    flyers.emplace_back(col, row, patrol);
    flyers.back().setTexture(resourceManager::getTexture(rend, flyers.back().getType()));
    dirty = true;
}

void Map::addWalker(int col, int row, int patrol) {
    walkers.emplace_back(col, row, patrol);
    walkers.back().setTexture(resourceManager::getTexture(rend, walkers.back().getType()));
    dirty = true;
}

bool Map::load(const std::string& path) {
    std::ifstream file(path);      // mở file để đọc
    if (!file.is_open()) {
        return false;
    }
    clear(); // xóa map cũ 

    std::string line;
    bool inPlatformBlock = false; // cờ kiểm tra xem có đang đọc platform không
    bool inDecorBlock = false;
    bool inEnemyBlock = false;

    while (std::getline(file, line)) {
        if (line == "<platform>") {
            inPlatformBlock = true;
            continue;
        }
        if (line == "</platform>") {
            inPlatformBlock = false;
            continue;
        }
        if (line == "<decor>") {
            inDecorBlock = true;
            continue;
        }
        if (line == "</decor>") {
            inDecorBlock = false;
            continue;
        }
        if (line == "<enemy>") {
            inEnemyBlock = true;
            continue;
        }
        if (line == "</enemy>") {
            inEnemyBlock = false;
            continue;
        }

        if (inPlatformBlock) {
            std::istringstream ss(line); // chuyển thành giống như cin 
            int col, row, srcX, srcY;
            std::string texKey, animType;

            ss >> col >> row >> texKey >> srcX >> srcY >> animType;
            addPlatform(col, row, texKey, srcX, srcY, animType);
        }

        if (inDecorBlock) {
            std::istringstream ss(line); // chuyển thành giống như cin 
            int col, row, srcX, srcY;
            std::string texKey, animType;

            ss >> col >> row >> texKey >> srcX >> srcY >> animType;
            addDecor(col, row, texKey, srcX, srcY, animType);
        }

        if (inEnemyBlock) {
            std::istringstream ss(line);
            int col, row, patrol;
            std::string type;

            if (ss >> col >> row >> type >> patrol) {
                if (type == "flyer") addFlyer(col, row, patrol);
                else if (type == "walker") addWalker(col, row, patrol);
                else std::cout << "Khong biet loai quai: " << type << std::endl;
            }
        }
    }

    dirty = false;
    return true;
}

/// <summary>
/// Lưu màn nếu dirty = false;
/// </summary>
/// <param name="path"></param>
/// <returns></returns>
bool Map::save(const std::string& path) {
    
    std::ofstream file(path);      // mở file để ghi ( xóa luôn nội dung cũ )
    if (!file.is_open()) {         // kiểm tra mở file có thành công không
        std::cout << "khong the mo file " << std::endl;
        return false;
    }

    std::cout << "bat dau ghi file";
    // Ghi các platform vào file .
    file << "<platform>" << std::endl;
    for (platform& p : plat) {
        file << p.getCol() << " " << p.getRow() << " "
            << p.getType() << " " << p.getSrcX() << " "
            << p.getSrcY() << " " << p.getTypeFrame() << std::endl;
    }
    file << "</platform>" << std::endl;

    // Ghi các decor vào file .
    file << "<decor>" << std::endl;
    for (decor& d : decorList) {
        file << d.getCol() << " " << d.getRow() << " "
            << d.getType() << " " << d.getSrcX() << " "
            << d.getSrcY() << " " << d.getTypeFrame() << std::endl;
    }
    file << "</decor>" << std::endl;

    // Ghi enemy vào file
    file << "<enemy>" << std::endl;
    for (flyer& f : flyers) {
        file << f.getCol() << " " << f.getRow() << " "
            << f.getType() << " " << f.getPatrol() << std::endl;
    }
    for (walker& w : walkers) {
        file << w.getCol() << " " << w.getRow() << " "
            << w.getType() << " " << w.getPatrol() << std::endl;
    }
    file << "</enemy>" << std::endl;

    // Đóng file .
    file.close();
    return true;
}

void Map::updateRenderRect() {
    mainPlayer.updRenderRect(cam);
    for (platform& x : plat) x.updRenderRect(cam);
    for (decor& d : decorList) d.updRenderRect(cam);
    for (flyer& f : flyers) f.updRenderRect(cam);
    for (walker& w : walkers) w.updRenderRect(cam);
}