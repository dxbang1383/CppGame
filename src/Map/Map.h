#ifndef MAP_H
#define MAP_H

#include <SDL3/SDL.h>
#include <iostream>
#include <vector>
#include <string>

#include "../GameObject/Enemy/enemy.h"
#include "../engine/camera.h"
#include "../GameObject/Platform/platform.h"
#include "../GameObject/Platform/switch.h"
#include "../GameObject/Platform/ladder.h"
#include "../GameObject/Platform/spike.h"

#include "../GameObject/Player/player.h"
#include "../GameObject/Platform/decor.h"
#include "../GameObject/Special/itembox.h"
#include "../GameObject/Special/item.h"
#include "../engine/resourceManager.h"


class Map {
private:
    camera cam = camera();
    player mainPlayer;
    std::vector<enemy> enemies;
    std::vector<platform> plat;
    std::vector<decor> decorList;
    std::vector<Switch> switches;
    std::vector<itemBox> boxes;
    std::vector<Item> items;


    SDL_Texture* bkg = nullptr;

    int startCol = 0, startRow = 0;       // điểm xuất phát
    int goalCol = 0, goalRow = 0;       // đích
    bool hasGoal = false;

    int cols = 0, rows = 0;               // kích thước map, tính bằng Ô
    std::string name;
    bool dirty = false;                   // có thay đổi chưa lưu

    std::string type;
    SDL_Renderer* rend = nullptr; // tam thoi lay renderer tu add texture

public:
    Map();
    // đọc / ghi file 
    bool load(const std::string& path);
    bool save(const std::string& path);
    void clear();

    // Gán texture cho TOÀN BỘ object — gọi ngay sau load()
    void addTextures(SDL_Renderer* renderer);

    // sửa map (editor dùng)
    void addPlatform(int col, int row, const std::string& texKey, int srcX, int srcY);
    void addDecor(int col, int row, const std::string& texKey, int srcX, int srcY);
    void addEnemy(int col, int row, const std::string& texKey, int srcX, int srcY);

    bool eraseAt(int col, int row, char layer);

    void setStart(int col, int row) {
        this->startCol = col;
        this->startRow = row;
    }
    void setGoal(int col, int row) {
        this->goalCol = col;
        this->goalRow = row;
    }

    SDL_Texture* getBkg() { return bkg; }
    std::vector<enemy>& getEnemies() { return enemies; }
    std::vector<platform>& getPlatforms() { return plat; }
    std::vector<decor>& getDecors() { return decorList; }
    std::vector<Switch>& getSwitches() { return switches; }
    std::vector<itemBox>& getBoxes() { return boxes; }
    std::vector<Item>& getItems() { return items; }
    player& getPlayer() { return mainPlayer; }
    float getStartX() const { return startCol * platform::TILE_SIZE; }
    float getStartY() const { return startRow * platform::TILE_SIZE; }
    camera& getCam() { return cam; }

    void updateRenderRect();
    void addTile();
    bool isDirty() const { return dirty; }

};

#endif // !MAP_H
