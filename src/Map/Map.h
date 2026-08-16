#ifndef MAP_H
#define MAP_H

#include <SDL3/SDL.h>
#include <iostream>
#include <vector>
#include <string>

#include "../GameObject/Enemy/enemy.h"
#include "../GameObject/Enemy/flyer.h"
#include "../GameObject/Enemy/walker.h"
#include "../engine/camera.h"
#include "../GameObject/Platform/platform.h"
#include "../GameObject/Player/player.h"
#include "../GameObject/Platform/decor.h"
#include "../engine/resourceManager.h"
#include "../engine/UI/Palette.h"
#include <fstream>   // std::ofstream, std::ifstream
#include <sstream>   // std::istringstream

class Map {
private:
    camera cam = camera();
    player mainPlayer;
    std::vector<flyer> flyers;
    std::vector<walker> walkers;
    std::vector<platform> plat;
    std::vector<decor> decorList;

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
    void addPlatform(int col, int row, std::string texKey, int srcX, int srcY, std::string animType);
    void addDecor(int col, int row, std::string texKey, int srcX, int srcY, std::string animType);
    void addFlyer(int col, int row, int patrol);
    void addWalker(int col, int row, int patrol);

    bool eraseAt(int col, int row, TileLayer layer);

    void setStart(int col, int row) {
        this->startCol = col;
        this->startRow = row;
    }
    void setGoal(int col, int row) {
        this->goalCol = col;
        this->goalRow = row;
    }

    SDL_Texture* getBkg() { return bkg; }
    std::vector<flyer>& getFlyers() { return flyers; }
    std::vector<walker>& getWalkers() { return walkers; }
    std::vector<platform>& getPlatforms() { return plat; }
    std::vector<decor>& getDecors() { return decorList; }
    player& getPlayer() { return mainPlayer; }
    float getStartX() const { return startCol * platform::TILE_SIZE; }
    float getStartY() const { return startRow * platform::TILE_SIZE; }
    camera& getCam() { return cam; }
    int xScreenToCol(float mouseClickX) {
        return floor(cam.xScreenToWorld(mouseClickX) / platform::TILE_SIZE);
    }
    int yScreenToRow(float mouseClickY) {
        return floor(cam.yScreenToWorld(mouseClickY) / platform::TILE_SIZE);
    }
    void updateRenderRect();
    
    void addTile();
    bool isDirty() const { return dirty; }

};

#endif // !MAP_H
