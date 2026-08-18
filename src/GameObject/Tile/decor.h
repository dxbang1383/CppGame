#ifndef DECOR_H
#define DECOR_H

#include <string>
#include "tile.h"

/*
	O trang tri - khong co va cham. Co hai dang:

	  TINH  : cat tu sprite sheet -> can texKey + srcX + srcY
	  DONG  : them typeAni de doi khung theo thoi gian

	typeAni chon huong nhay sang khung ke tiep tren sheet:
	  "x++"  ->  khung ke tiep nam BEN PHAI
	  "y++"  ->  khung ke tiep nam BEN DUOI
*/
class decor : public tile {
private:
	bool animationEnable = false;
	float timeFrame = 0.25f;   // moi khung giu bao lau
	float time = 0.0f;         // dong ho dem cho khung hien tai
	int frame = 1;             // 1 = khung goc, 2 = khung ke tiep
	std::string typeFrame = "";

public:
	using tile::tile;   // ke thua toan bo constructor cua tile (dang TINH)

	// Decor DONG
	decor(int m, int n, std::string t, int srcX, int srcY, std::string typeAni);

	bool hasAnim() const { return animationEnable; }

	void update(float deltaTime) override;
	void render(SDL_Renderer* renderer) override;
};

#endif // !DECOR_H
