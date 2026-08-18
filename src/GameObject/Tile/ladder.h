#ifndef LADDER_H
#define LADDER_H

#include <SDL3/SDL.h>
#include <string>
#include <../src/GameObject/Tile/tile.h>

/*
	Nac thang tren luoi o. Nguoi choi cham vao thi treo va leo duoc.
	Ke thua tile nen dung san texture / renderRect / updRenderRect(camera) / render().
*/
class ladder : public tile {
public:
	ladder(int col, int row, std::string texKey = "ladder") : tile(col, row, texKey) {

	}
};

#endif // !LADDER_H
