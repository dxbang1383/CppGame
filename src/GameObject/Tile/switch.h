#ifndef SWITCH_H
#define SWITCH_H

#include <SDL3/SDL.h>
#include <string>
#include "tile.h"

/*
	Cong tac tren luoi o. Nguoi choi cham vao thi kich hoat,
	sceneMain se xoa cac spike quanh no.

	Anh switch gom 2 khung nam ngang:  [ TAT | BAT ]
	setTexture cat nua trai, trigger() doi sang nua phai.

	Ke thua tile nen dung san texture / renderRect / updRenderRect(camera) / render().
*/
class Switch : public tile {
private:
	bool  isActivated = false;
	float frameW = 0.0f;
	float frameH = 0.0f;

public:
	Switch(int col, int row, std::string texKey = "switch")
		: tile(col, row, texKey) {
	}

	// Che setTexture cua lop cha de tinh vung cat theo trang thai
	void setTexture(SDL_Texture* tex) {
		gameObject::setTexture(tex);
		if (tex == nullptr) return;

		float texW = 0.0f, texH = 0.0f;
		SDL_GetTextureSize(tex, &texW, &texH);

		frameW = texW / 2.0f;
		frameH = texH;

		float sx = 0.0f;
		if (isActivated) {
			sx = frameW;
		}
		setSrcRect({ sx, 0.0f, frameW, frameH });
	}

	void trigger() {
		if (isActivated) return;
		isActivated = true;
		setSrcRect({ frameW, 0.0f, frameW, frameH });   // doi sang khung BAT
	}

	bool getIsActivated() const { return isActivated; }
};

#endif // !SWITCH_H
