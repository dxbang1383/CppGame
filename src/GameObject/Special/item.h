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

	void setIVelocityY(double velocity);
	void update();
	void render(SDL_Renderer* renderer);
	ItemType getItemType() const;
	bool isCollected() const;
	void collect();
	double getIVelocityX() const;
	double getIVelocityY() const;
};