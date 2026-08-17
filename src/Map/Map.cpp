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
        // sprite animation rieng (neu co)
        if (d.hasAnim()) {
            d.getAnim().setTexture(resourceManager::getTexture(renderer, d.getAnimKey()));
        }
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
    // Duyet NGUOC de xoa dung tile ve sau cung (tile nam tren cung)

    if (layer == TileLayer::LAYER_PLATFORM) {
        for (int i = (int)plat.size() - 1; i >= 0; i--) {
            if (plat[i].getCol() == col && plat[i].getRow() == row) {
                plat.erase(plat.begin() + i);
                dirty = true;
                return true;
            }
        }
    }
    else if (layer == TileLayer::LAYER_DECOR) {
        for (int i = (int)decorList.size() - 1; i >= 0; i--) {
            if (decorList[i].getCol() == col && decorList[i].getRow() == row) {
                decorList.erase(decorList.begin() + i);
                dirty = true;
                return true;
            }
        }
    }
    else if (layer == TileLayer::LAYER_ENEMY) {
        for (int i = (int)flyers.size() - 1; i >= 0; i--) {
            if (flyers[i].getCol() == col && flyers[i].getRow() == row) {
                flyers.erase(flyers.begin() + i);
                dirty = true;
                return true;
            }
        }
        for (int i = (int)walkers.size() - 1; i >= 0; i--) {
            if (walkers[i].getCol() == col && walkers[i].getRow() == row) {
                walkers.erase(walkers.begin() + i);
                dirty = true;
                return true;
            }
        }
    }
    return false;
}

void Map::addPlatform(int col, int row, std::string texKey,
                        int srcX, int srcY) {
    plat.emplace_back(col, row, texKey, srcX, srcY);
    plat.back().setTexture(resourceManager::getTexture(rend, texKey));
    dirty = true;
}

void Map::addDecor(int col, int row, std::string texKey,
                        int srcX, int srcY, std::string animKey) {
    decorList.emplace_back(col, row, texKey, srcX, srcY, animKey);
    decor& d = decorList.back();

    // hinh du phong
    d.setTexture(resourceManager::getTexture(rend, texKey));

    // sprite animation rieng trong Tiles/Animation
    if (d.hasAnim()) {
        d.getAnim().setTexture(resourceManager::getTexture(rend, animKey));
    }
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
            std::string texKey;

            if (ss >> col >> row >> texKey >> srcX >> srcY) {
                addPlatform(col, row, texKey, srcX, srcY);
            }
        }

        if (inDecorBlock) {
            std::istringstream ss(line); // chuyển thành giống như cin 
            int col, row, srcX, srcY;
            std::string texKey, animKey;

            // animKey = "-" static
            if (ss >> col >> row >> texKey >> srcX >> srcY >> animKey) {
                addDecor(col, row, texKey, srcX, srcY, animKey);
            }
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

    file << "<platform>\n";
    for (platform& p : plat) {
        file << p.getCol() << " " << p.getRow() << " "
            << p.getType() << " " << p.getSrcX() << " "
            << p.getSrcY() << "\n";
    }
    file << "</platform>\n";

    // Ghi các decor vào file 
    file << "<decor>\n";
    for (decor& d : decorList) {
        file << d.getCol() << " " << d.getRow() << " "
            << d.getType() << " " << d.getSrcX() << " "
            << d.getSrcY() << " " << d.getAnimKey() << "\n";
    }
    file << "</decor>\n";

    // Ghi enemy vào file
    file << "<enemy>\n";
    for (flyer& f : flyers) {
        file << f.getCol() << " " << f.getRow() << " "
            << f.getType() << " " << f.getPatrol() << "\n";
    }
    for (walker& w : walkers) {
        file << w.getCol() << " " << w.getRow() << " "
            << w.getType() << " " << w.getPatrol() << "\n";
    }
    file << "</enemy>\n";

    // Đóng file .
    file.close();
    dirty = false;
    return true;
}

void Map::updateRenderRect() {
    mainPlayer.updRenderRect(cam);
    for (platform& x : plat) x.updRenderRect(cam);
    for (decor& d : decorList) d.updRenderRect(cam);
    for (flyer& f : flyers) f.updRenderRect(cam);
    for (walker& w : walkers) w.updRenderRect(cam);
}