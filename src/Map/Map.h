#ifndef MAP_H
#define MAP_H

#include <SDL3/SDL.h>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include "../GameObject/Enemy/enemy.h"
#include "../GameObject/Enemy/flyer.h"
#include "../GameObject/Enemy/walker.h"
#include "../engine/camera.h"
#include "../GameObject/Tile/platform.h"
#include "../GameObject/Player/player.h"
#include "../GameObject/Tile/decor.h"
#include "../engine/resourceManager.h"
#include "../engine/UI/Palette.h"
#include "../GameObject/Tile/ladder.h"
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
    std::vector<ladder> ladders;

    SDL_Texture* bkg = nullptr;

    int startCol = 0, startRow = 0; // điểm xuất phát
    int goalCol = 0, goalRow = 0; // đích
    bool hasGoal = false;

    int cols = 0, rows = 0; // kích thước map, tính bằng Ô
    std::string name;
    bool dirty = false;  // có thay đổi chưa lưu

    std::string type;
    SDL_Renderer* rend = nullptr; // tam thoi lay renderer tu add texture

public:
    Map();
    // đọc / ghi file 
    bool load(const std::string& path);
    bool save(const std::string& path);
    void clear();

    void addTextures(SDL_Renderer* renderer);

    void addPlatform(int col, int row, std::string texKey, int srcX, int srcY);


    void addDecor(int col, int row, std::string texKey, int srcX, int srcY);
    void addDecorAnim(int col, int row, std::string animKey);
    void addFlyer(int col, int row, int patrol);
    void addWalker(int col, int row, int patrol);
    void addLadder(int col, int row, std::string texKey);
    void addWalker(int col, int row, int patrol, int kind = 1);

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
    std::vector<ladder>& getLadders() { return ladders; }

    player& getPlayer() { return mainPlayer; }
    // Chuyển từ địa chỉ col sang x 
    float getStartX() const { return startCol * tile::TILE_SIZE; }
    // Chuyển từ địa chỉ row sang y 
    float getStartY() const { return startRow * tile::TILE_SIZE; }
    camera& getCam() { return cam; }
    int xScreenToCol(float mouseClickX) {
        return floor(cam.xScreenToWorld(mouseClickX) / tile::TILE_SIZE);
    }
    int yScreenToRow(float mouseClickY) {
        return floor(cam.yScreenToWorld(mouseClickY) / tile::TILE_SIZE);
    }
    void updateRenderRect();
    
    void addTile();
    bool isDirty() const { return dirty; }

};

#endif // !MAP_H
