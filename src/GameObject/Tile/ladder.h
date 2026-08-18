#ifndef LADDER_H
#define LADDER_H

#include <SDL3/SDL.h>
#include <string>
#include <../src/GameObject/Tile/tile.h>

class ladder : public tile {
public:
	ladder(int col, int row, std::string texKey = "ladder") : tile(col, row, texKey) {

	}
};

#endif
