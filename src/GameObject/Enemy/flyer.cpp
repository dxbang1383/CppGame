#include "flyer.h"

flyer::flyer(int col, int row, int patrol) : enemy(col, row, patrol) {
	type = "flyer";
	anim = Animation(3, 0.15f);

	// bay trai phai 
	patrolMinX = getX() - 4 * tile::TILE_SIZE;
	patrolMaxX = getX() + 4 * tile::TILE_SIZE;
}

void flyer::update(float deltaTime) {
	if (!alive) return;

	// khong co trong luc, chi di ngang
	velocityX = speed * direction;
	setX(getX() + velocityX * deltaTime);

	if (getX() < patrolMinX) { setX(patrolMinX); direction = 1; }
	else if (getX() > patrolMaxX) { setX(patrolMaxX); direction = -1; }

	anim.update(deltaTime);
}
