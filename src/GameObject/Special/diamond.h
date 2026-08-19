#ifndef DIAMOND_H
#define DIAMOND_H

#include <SDL3/SDL.h>
#include <string>
#include <../src/GameObject/Tile/tile.h>

class Diamond : public tile {
private:
    bool collected = false;
    int value = 5; 

public:
    using tile::tile; 

    bool isCollected() const { return collected; }
    void setCollected(bool state) { collected = state; }
    int getValue() const { return value; }
};

#endif // !DIAMOND_H