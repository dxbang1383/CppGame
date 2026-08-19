#pragma once

#include <SDL3/SDL.h>
#include "../src/GameObject/gameObject.h"

enum class ItemType {
	COIN1, 
	STAR,
	DOUBLE_JUMP,
	NO_GRAVITY,
	HIGH_JUMP,
	HEART,
	SPEED
};

class Item : public gameObject
{
private:
	ItemType type;
	bool collected = false;

	double IvelocityX = 0.0;
	double IvelocityY = 0.0;

public:
	Item(
		double x,
		double y,
		double width,
		double height,
		ItemType type
	);

	// Theo dia chi o tren map (item dat san trong file).
	// Sau khi bat ra khoi hop thi Item bay tu do nen KHONG ke thua specialObject.
	Item(int col, int row, ItemType type);

	static constexpr float TILE_SIZE = 36;

	// Chi dung luc ghi file, khi item con dung yen tai o cua no
	int getCol() const { return (int)(getX() / TILE_SIZE); }
	int getRow() const { return (int)(getY() / TILE_SIZE); }

	void setIVelocityY(double velocity);
	void update(float deltaTime) override;
	void render(SDL_Renderer* renderer);
	ItemType getItemType() const;
	bool isCollected() const;
	void collect();
	double getIVelocityX() const;
	double getIVelocityY() const;
};