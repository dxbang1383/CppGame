#pragma once

#include <SDL3/SDL.h>
#include "../src/GameObject/gameObject.h"

enum class BoxType {
	COIN,
	QUESTION,
	ITEM
};


class itemBox : public gameObject
{
private:
	BoxType boxType;

	bool activated = false;
	int currentFrame = 0;
	bool bouncing = false;
	float bounceOffset = 0.0f;
	float bounceVelocity = 0.0f;

public:
	itemBox(
		double x,
		double y,
		double width,
		double height,
		BoxType type
	);
	// Render
	void render(SDL_Renderer* renderer);

	// Player run cung tuong duoi
	bool hitFromBelow(double playerX, double playerY);

	// Kich hoat hop
	void activate();

	// Update animation
	void update(float deltaTime);

	// Getter
	bool isActivated() const;
	bool isBouncing() const;

	BoxType getBoxType() const;
	

	// Lay vi tri reward

	double getRewardX() const;
	double getRewardY() const;

};