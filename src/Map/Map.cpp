#include "Map.h"

// Khoa texture cua tung loai hop / vat pham
static const char* boxTexKey(BoxType t) {
    if (t == BoxType::QUESTION) return "box_question";
    if (t == BoxType::ITEM)     return "box_item";
    return "box_coin";
}

static const char* itemTexKey(ItemType t) {
    switch (t) {
    case ItemType::STAR:        return "i_star";
    case ItemType::SPEED:       return "i_speed";
    case ItemType::HEART:       return "i_heart";
    case ItemType::NO_GRAVITY:  return "i_nogravity";
    case ItemType::DOUBLE_JUMP: return "i_doublejump";
    case ItemType::HIGH_JUMP:   return "i_highjump";
    }
    return "i_coin";
}


Map::Map() : mainPlayer(0, 0) {
}

void Map::clear() {
    plat.clear();
    decorList.clear();
    flyers.clear();
    walkers.clear();
    ladders.clear();
    switches.clear();
    spikes.clear();
    boxes.clear();
    items.clear();
    coins.clear();
    diamonds.clear();

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
        // getType() la khoa texture cho ca hai dang: sheet (tinh) hoac sprite (dong)
        if (d.hasAnim())
            d.getAnim().setTexture(resourceManager::getTexture(renderer, d.getType()));
        else
            d.setTexture(resourceManager::getTexture(renderer, d.getType()));
    }

    for (ladder& l : ladders) {
        l.setTexture(resourceManager::getTexture(renderer, l.getType()));
    }

    for (Switch& sw : switches) {
        sw.setTexture(resourceManager::getTexture(renderer, sw.getType()));
    }

    for (spike& sp : spikes) {
        sp.setTexture(resourceManager::getTexture(renderer, sp.getType()));
    }

    for (itemBox& b : boxes) {
        b.setTexture(resourceManager::getTexture(renderer, boxTexKey(b.getBoxType())));
    }

    for (Item& it : items) {
        it.setTexture(resourceManager::getTexture(renderer, itemTexKey(it.getItemType())));
    }

    for (Coin& c : coins) {
        c.setTexture(resourceManager::getTexture(renderer, "coin"));
    }

    for (Diamond& dia : diamonds) {
        dia.setTexture(resourceManager::getTexture(renderer, "diamond"));
    }
    // Animation player
    SDL_Texture* idle = resourceManager::getTexture(renderer, "player_idle");
    SDL_Texture* run = resourceManager::getTexture(renderer, "player_run");
    SDL_Texture* jump = resourceManager::getTexture(renderer, "player_jump");
    SDL_Texture* def = resourceManager::getTexture(renderer, "player");

    player& p = getPlayer();
    p.setIdleTexture(idle ? idle : def);
    p.setRunTexture(run ? run : def);
    p.setJumpTexture(jump ? jump : def);
    p.setTexture(idle ? idle : def);

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
    else if (layer == TileLayer::LAYER_DECOR || layer == TileLayer::LAYER_DECOR_ANIM) {
        for (int i = (int)decorList.size() - 1; i >= 0; i--) {
            if (decorList[i].getCol() == col && decorList[i].getRow() == row) {
                decorList.erase(decorList.begin() + i);
                dirty = true;
                return true;
            }
        }
    }
    else if (layer == TileLayer::LAYER_LADDER) {
        for (int i = (int)ladders.size() - 1; i >= 0; i--) {
            if (ladders[i].getCol() == col && ladders[i].getRow() == row) {
                ladders.erase(ladders.begin() + i);
                dirty = true;
                return true;
            }
        }
    }
    else if (layer == TileLayer::LAYER_SWITCH) {
        for (int i = (int)switches.size() - 1; i >= 0; i--) {
            if (switches[i].getCol() == col && switches[i].getRow() == row) {
                switches.erase(switches.begin() + i);
                dirty = true;
                return true;
            }
        }
    }
    else if (layer == TileLayer::LAYER_SPIKE) {
        for (int i = (int)spikes.size() - 1; i >= 0; i--) {
            if (spikes[i].getCol() == col && spikes[i].getRow() == row) {
                spikes.erase(spikes.begin() + i);
                dirty = true;
                return true;
            }
        }
    }
    else if (layer == TileLayer::LAYER_BOX) {
        for (int i = (int)boxes.size() - 1; i >= 0; i--) {
            if (boxes[i].getCol() == col && boxes[i].getRow() == row) {
                boxes.erase(boxes.begin() + i);
                dirty = true;
                return true;
            }
        }
    }
    else if (layer == TileLayer::LAYER_ITEM) {
        for (int i = (int)items.size() - 1; i >= 0; i--) {
            if (items[i].getCol() == col && items[i].getRow() == row) {
                items.erase(items.begin() + i);
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
    else if (layer == TileLayer::LAYER_COIN) {
        for (int i = (int)coins.size() - 1; i >= 0; i--) {
            if (coins[i].getCol() == col && coins[i].getRow() == row) {
                coins.erase(coins.begin() + i);
                dirty = true;
                return true;
            }
        }
    }
    else if (layer == TileLayer::LAYER_DIAMOND) {
        for (int i = (int)diamonds.size() - 1; i >= 0; i--) {
            if (diamonds[i].getCol() == col && diamonds[i].getRow() == row) {
                diamonds.erase(diamonds.begin() + i);
                dirty = true;
                return true;
            }
        }
    }
    return false;
}

void Map::addLadder(int col, int row, std::string texKey) {
    ladders.emplace_back(col, row, texKey);
    ladders.back().setTexture(resourceManager::getTexture(rend, texKey));
    dirty = true;
}

void Map::addBox(int col, int row, BoxType type) {
    boxes.emplace_back(col, row, type);
    boxes.back().setTexture(resourceManager::getTexture(rend, boxTexKey(type)));
    dirty = true;
}

void Map::addItem(int col, int row, ItemType type) {
    items.emplace_back(col, row, type);
    items.back().setTexture(resourceManager::getTexture(rend, itemTexKey(type)));
    dirty = true;
}

void Map::addSwitch(int col, int row, std::string texKey) {
    switches.emplace_back(col, row, texKey);
    switches.back().setTexture(resourceManager::getTexture(rend, texKey));
    dirty = true;
}

void Map::addSpike(int col, int row, std::string texKey) {
    spikes.emplace_back(col, row, texKey);
    spikes.back().setTexture(resourceManager::getTexture(rend, texKey));
    dirty = true;
}

void Map::addPlatform(int col, int row, std::string texKey,
                        int srcX, int srcY) {
    plat.emplace_back(col, row, texKey, srcX, srcY);
    plat.back().setTexture(resourceManager::getTexture(rend, texKey));
    dirty = true;
}

void Map::addDecor(int col, int row, std::string texKey, int srcX, int srcY) {
    decorList.emplace_back(col, row, texKey, srcX, srcY);
    decorList.back().setTexture(resourceManager::getTexture(rend, texKey));
    dirty = true;
}

void Map::addDecorAnim(int col, int row, std::string animKey) {
    decorList.emplace_back(col, row, animKey);
    decorList.back().getAnim().setTexture(resourceManager::getTexture(rend, animKey));
    dirty = true;
}

void Map::addFlyer(int col, int row, int patrol) {
    flyers.emplace_back(col, row, patrol);
    flyers.back().setTexture(resourceManager::getTexture(rend, flyers.back().getType()));
    dirty = true;
}

void Map::addWalker(int col, int row, int patrol, int kind) {
    walkers.emplace_back(col, row, patrol, kind);
    walkers.back().setTexture(resourceManager::getTexture(rend, walkers.back().getType()));
    dirty = true;
}

void Map::addCoin(int col, int row) {
    coins.emplace_back(col, row, "coin");
    coins.back().setTexture(resourceManager::getTexture(rend, "coin"));
    dirty = true;
}

void Map::addDiamonds(int col, int row) {
    diamonds.emplace_back(col, row, "diamond");
    diamonds.back().setTexture(resourceManager::getTexture(rend, "diamond"));
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
    bool inStateBlock = false;
    bool inLadderBlock = false;
    bool inAnimBlock = false;
    bool inSwitchBlock = false;
    bool inSpikeBlock = false;
    bool inBoxBlock = false;
    bool inItemBlock = false;
    bool inCoinBlock = false;
    bool inDiamondBlock = false;

    while (std::getline(file, line)) {
        if (true) {
            if (line == "<state>") {
                inStateBlock = true;
                continue;
            }
            if (line == "</state>") {
                inStateBlock = false;
                continue;
            }
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
            if (line == "<animation>") {
                inAnimBlock = true;
                continue;
            }
            if (line == "</animation>") {
                inAnimBlock = false;
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
            if (line == "<ladder>") {
                inLadderBlock = true;
                continue;
            }
            if (line == "</ladder>") {
                inLadderBlock = false;
                continue;
            }
            if (line == "<switch>") {
                inSwitchBlock = true;
                continue;
            }
            if (line == "</switch>") {
                inSwitchBlock = false;
                continue;
            }
            if (line == "<spike>") {
                inSpikeBlock = true;
                continue;
            }
            if (line == "</spike>") {
                inSpikeBlock = false;
                continue;
            }
            if (line == "<box>") {
                inBoxBlock = true;
                continue;
            }
            if (line == "</box>") {
                inBoxBlock = false;
                continue;
            }
            if (line == "<item>") {
                inItemBlock = true;
                continue;
            }
            if (line == "</item>") {
                inItemBlock = false;
                continue;
            }
            if (line == "<coin>") {
                inCoinBlock = true;  
                continue;
            }
            if (line == "</coin>") {
                inCoinBlock = false;
                continue;
            }
            if (line == "<diamond>") {
                inDiamondBlock = true; 
                continue;
            }
            if (line == "</diamond>") {
                inDiamondBlock = false;
                continue;
            }
        }

        if (inStateBlock) {
            std::istringstream ss(line); // chuyển thành giống như cin 
            ss >> startCol >> startRow >> goalCol >> goalRow;
            mainPlayer.setPosition(getStartX(), getStartY());
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
            std::string texKey;

            if (ss >> col >> row >> texKey >> srcX >> srcY) {
                addDecor(col, row, texKey, srcX, srcY);
            }
        }

        if (inAnimBlock) {
            std::istringstream ss(line);
            int col, row;
            std::string animKey;

            if (ss >> col >> row >> animKey) {
                addDecorAnim(col, row, animKey);
            }
        }

        if (inEnemyBlock) {
            std::istringstream ss(line);
            int col, row, patrol;
            std::string type;

            if (ss >> col >> row >> type >> patrol) {
                if (type == "flyer") addFlyer(col, row, patrol);
                else if (type == "walker" || type == "walker1") addWalker(col, row, patrol, 1);
                else if (type == "walker2") addWalker(col, row, patrol, 2);
                else if (type == "walker3") addWalker(col, row, patrol, 3);
                else std::cout << "Khong biet loai quai: " << type << std::endl;
            }
        }

        if (inLadderBlock) {
            std::istringstream ss(line);
            int col, row;
            std::string texKey;
            ss >> col >> row >> texKey;
            addLadder(col, row, texKey);
        }

        if (inSwitchBlock) {
            std::istringstream ss(line);
            int col, row;

            if (ss >> col >> row) {
                addSwitch(col, row);
            }
        }

        if (inSpikeBlock) {
            std::istringstream ss(line);
            int col, row;

            if (ss >> col >> row) {
                addSpike(col, row);
            }
        }

        if (inBoxBlock) {
            std::istringstream ss(line);
            int col, row;
            std::string type;

            if (ss >> col >> row >> type) {
                if (type == "coin")          addBox(col, row, BoxType::COIN);
                else if (type == "question") addBox(col, row, BoxType::QUESTION);
                else if (type == "item")     addBox(col, row, BoxType::ITEM);
                else std::cout << "Khong biet loai hop: " << type << std::endl;
            }
        }

        if (inItemBlock) {
            std::istringstream ss(line);
            int col, row;
            std::string type;

            if (ss >> col >> row >> type) {
                if (type == "coin")             addItem(col, row, ItemType::COIN1);
                else if (type == "star")        addItem(col, row, ItemType::STAR);
                else if (type == "speed")       addItem(col, row, ItemType::SPEED);
                else if (type == "heart")       addItem(col, row, ItemType::HEART);
                else if (type == "nogravity")   addItem(col, row, ItemType::NO_GRAVITY);
                else if (type == "doublejump")  addItem(col, row, ItemType::DOUBLE_JUMP);
                else if (type == "highjump")    addItem(col, row, ItemType::HIGH_JUMP);
                else std::cout << "Khong biet loai vat pham: " << type << std::endl;
            }
        }

        if (inCoinBlock) {
            std::istringstream ss(line);
            int col, row;
            if (ss >> col >> row) {
                addCoin(col, row); // Hàm addCoin tự định nghĩa trong Map
            }
        }

        if (inDiamondBlock) {
            std::istringstream ss(line);
            int col, row;
            if (ss >> col >> row) {
                addDiamonds(col, row); // Hàm addDiamond tự định nghĩa trong Map
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
    std::cout << "Save Map " << std::endl;
    file << "<state>\n";
    file << startCol << " " << startRow << " " 
        << goalCol << " " << goalRow << "\n";
    file << "</state>\n";

    file << "<platform>\n";
    for (platform& p : plat) {
        file << p.getCol() << " " << p.getRow() << " "
            << p.getType() << " " << p.getSrcX() << " "
            << p.getSrcY() << "\n";
    }
    file << "</platform>\n";

    // Ghi các decor vào file 
    // Decor TINH
    file << "<decor>\n";
    for (decor& d : decorList) {
        if (d.hasAnim()) continue;
        file << d.getCol() << " " << d.getRow() << " "
            << d.getType() << " " << d.getSrcX() << " "
            << d.getSrcY() << "\n";
    }
    file << "</decor>\n";

    // Decor DONG
    file << "<animation>\n";
    for (decor& d : decorList) {
        if (!d.hasAnim()) continue;
        file << d.getCol() << " " << d.getRow() << " "
            << d.getType() << "\n";
    }
    file << "</animation>\n";

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

    // Ghi laddder vào file 
    file << "<ladder>\n";
    for (ladder& l : ladders) {
        file << l.getCol() << " " << l.getRow() << " "
            << l.getType() << "\n";
    }
    file << "</ladder>\n";

    // Ghi switch vào file
    file << "<switch>\n";
    for (Switch& sw : switches) {
        file << sw.getCol() << " " << sw.getRow() << "\n";
    }
    file << "</switch>\n";

    // Ghi spike vào file
    file << "<spike>\n";
    for (spike& sp : spikes) {
        file << sp.getCol() << " " << sp.getRow() << "\n";
    }
    file << "</spike>\n";

    // Ghi box vào file
    file << "<box>\n";
    for (itemBox& b : boxes) {
        std::string t = "coin";
        if (b.getBoxType() == BoxType::QUESTION) t = "question";
        else if (b.getBoxType() == BoxType::ITEM) t = "item";

        file << b.getCol() << " " << b.getRow() << " " << t << "\n";
    }
    file << "</box>\n";

    // Ghi coin vao file
    file << "<coin>\n";
    for (Coin& c : coins) {
        file << c.getCol() << " " << c.getRow() << "\n";
    }
    file << "</coin>\n";

    // Ghi diamond vào file
    file << "<diamond>\n";
    for (Diamond& dia : diamonds) {
        file << dia.getCol() << " " << dia.getRow() << "\n";
    }
    file << "</diamond>\n";

    // Ghi item vào file
    file << "<item>\n";
    for (Item& it : items) {
        std::string t = "coin";
        switch (it.getItemType()) {
        case ItemType::STAR:        t = "star";       break;
        case ItemType::SPEED:       t = "speed";      break;
        case ItemType::HEART:       t = "heart";      break;
        case ItemType::NO_GRAVITY:  t = "nogravity";  break;
        case ItemType::DOUBLE_JUMP: t = "doublejump"; break;
        case ItemType::HIGH_JUMP:   t = "highjump";   break;
        }
        file << it.getCol() << " " << it.getRow() << " " << t << "\n";
    }
    file << "</item>\n";

    // Đóng file .
    file.close();
    dirty = false;
    return true;
}

void Map::updateRenderRect() {
    mainPlayer.updRenderRect(cam);
    for (platform& x : plat) x.updRenderRect(cam);
    for (decor& d : decorList) d.updRenderRect(cam);
    for (itemBox& box : boxes) box.updRenderRect(cam);
    for (Item& it : items) it.updRenderRect(cam);
    for (Switch& sw : switches) sw.updRenderRect(cam);
    for (flyer& f : flyers) f.updRenderRect(cam);
    for (walker& w : walkers) w.updRenderRect(cam);
    for (ladder& l : ladders) l.updRenderRect(cam);   // thang cũng theo camera
    for (spike& sp : spikes) sp.updRenderRect(cam);
    for (Coin& c : coins) c.updRenderRect(cam);
    for (Diamond& dia : diamonds) dia.updRenderRect(cam);
}