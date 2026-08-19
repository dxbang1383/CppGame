#include "item.h"

Item::Item(
	double x,
	double y,
	double width,
	double height,
	ItemType type
) : gameObject(x, y, width, height), type(type)
{
	collected = false;
	IvelocityX = 0.0;
	IvelocityY = 0.0;
}

Item::Item(int col, int row, ItemType type)
	: gameObject(col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE), type(type)
{
	collected = false;
	IvelocityX = 0.0;
	IvelocityY = 0.0;
}

void Item::update(float deltaTime) {
	if (collected) return;
	IvelocityY = IvelocityY + 500 * deltaTime;
	setX(getX() + IvelocityX * deltaTime);
	setY(getY() + IvelocityY * deltaTime);

}

void Item::render(SDL_Renderer* renderer) {
	if (collected) return;

	if (getTexture() != nullptr) {
		SDL_RenderTexture(renderer, getTexture(), nullptr, &renderRect);
	}
	else {

		SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
		SDL_RenderFillRect(renderer, &renderRect);
	}

}

void Item::collect() {
	collected = true;
}

ItemType Item::getItemType() const { return type; }
bool Item::isCollected() const { return collected; }
double Item::getIVelocityX() const { return IvelocityX; }
double Item::getIVelocityY() const { return IvelocityY; }
void Item::setIVelocityY(double velocity) {
	IvelocityY = velocity;
}

