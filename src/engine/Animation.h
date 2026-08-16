#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL3/SDL.h>

/*
	Moi Animation ung voi 1 file anh rieng, cac frame xep ngang tu trai sang phai.
	Kich thuoc 1 frame duoc tinh tu texture (texW / frameCount) nen khong can khai bao tay.
*/
class Animation {
private:
	SDL_Texture* texture = nullptr;

	int   frameCount = 1;      // so frame co trong file anh
	float frameTime = 0.1f;    // thoi gian moi frame (giay)

	float frameW = 0.0f;       // kich thuoc 1 frame, tinh trong setTexture
	float frameH = 0.0f;

	int   currentFrame = 0;    // trang thai dang chay
	float timer = 0.0f;

public:
	Animation() = default;
	Animation(int frameCount, float frameTime);

	// Goi sau khi da co renderer, vi texture chua ton tai luc khoi tao object
	void setTexture(SDL_Texture* tex);
	SDL_Texture* getTexture() const { return texture; }

	void update(float deltaTime);
	// Dua ve frame dau, chi goi khi muon animation chay lai tu dau
	void reset();

	// Hinh chu nhat cat tren sheet cua frame hien tai
	SDL_FRect getSrcRect() const;

	int getFrameCount() const { return frameCount; }
};

#endif // !ANIMATION_H
