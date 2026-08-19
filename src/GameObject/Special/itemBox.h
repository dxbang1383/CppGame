#pragma once

#include <SDL3/SDL.h>
#include "specialObject.h"

enum class BoxType {
	COIN,
	QUESTION,
	ITEM
};

class itemBox : public specialObject
{
private:
	static constexpr float FRAME_SIZE = 22.0f;

	BoxType boxType;

	bool activated = false;
	// chưa viết ---
	bool bouncing = false; // đang nảy 
	float bounceOffset = 0.0f; // độ lệch so với vị trí gốc
	float bounceVelocity = 0.0f; // vận tốc di chuyển của box khi nảy lên 

public:
	// khởi tạo bằng col row (world)
	itemBox(int col, int row, BoxType type);

	// Che setTexture cua lop cha de cat khung theo trang thai
	void setTexture(SDL_Texture* tex);

	// Kich hoat hop
	void activate();

	// Update animation
	void update(float deltaTime);

	// Getter
	bool isActivated() const;
	bool isBouncing() const;

	BoxType getBoxType() const;

	// vị trí item sinh ra
	double getRewardX() const;
	double getRewardY() const;

};
