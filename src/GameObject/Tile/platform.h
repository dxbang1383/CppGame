#ifndef PLATFORM_H
#define PLATFORM_H

#include "tile.h"
// co va cham voi nguoi choi tam thoi xu ly trong main
class platform : public tile {
public:
	using tile::tile;   // ke thua toan bo constructor cua tile
};

#endif // !PLATFORM_H
