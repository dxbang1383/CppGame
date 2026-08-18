#include "itemBox.h"

itemBox::itemBox(
	double x,
	double y,
	double width,
	double height,
	BoxType type
) : gameObject(x, y, width, height), boxType(type)
{
}

void itemBox::render(SDL_Renderer* renderer) {
	if (!getTexture()) {
		return;
	}

	SDL_FRect srcRect;
	srcRect.x = currentFrame * 22;
	srcRect.y = 0;

	srcRect.w = 22;
	srcRect.h = 22;

	SDL_RenderTexture(
		renderer,
		getTexture(),
		&srcRect,
		&renderRect
	);
}

bool itemBox::hitFromBelow(double playerX, double playerY) {
	if (activated) return false;

	double playerRight = playerX + getWidth();
	double boxRight = getX() + getWidth();

	double playerTop = playerY;

	bool horizontalOverlap =
		playerX < boxRight && playerRight > getX();
	
	bool verticalCollison =
		playerTop <= getY() + getHeight() &&
		playerTop >= getY() + getHeight() - 15;

	if (horizontalOverlap && verticalCollison) {
		activate();
		return true;
	}
	return false;
} 

void itemBox::activate() {
	if (activated) {
		return;
	}
	activated = true;
	currentFrame = 1;
}

void itemBox::update(float deltaTime) {
	if (!bouncing) {
		return;
	}

	bounceOffset += bounceVelocity * deltaTime;

	bounceVelocity += 500.0f * deltaTime;

	if (bounceOffset >= 0.0f) {
		bounceOffset = 0.0f;
		bounceVelocity = 0.0f;
		bouncing = false;
	}
}



bool itemBox::isActivated() const { return activated; }
bool itemBox::isBouncing() const { return bouncing; }
BoxType itemBox::getBoxType() const { return boxType; }

double itemBox::getRewardX() const { return getX() + getWidth() / 2.0; }
double itemBox::getRewardY() const { return getY() - getHeight() / 2.0; }
