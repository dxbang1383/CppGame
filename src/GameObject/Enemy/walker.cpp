#include "walker.h"

walker::walker(int col, int row, int patrol) : enemy(col, row, patrol) {
	type = "walker";
	anim = Animation(1, 0.15f);// tam thoi 1 drame

	patrolMinX = getX() - 3 * platform::TILE_SIZE;
	patrolMaxX = getX() + 3 * platform::TILE_SIZE;
}

void walker::update(float deltaTime) {
	if (!alive) return;
	// tam thoi chi udp theo truc x 

	velocityX = speed * direction;
	setX(getX() + velocityX * deltaTime);

	if (getX() < patrolMinX) { setX(patrolMinX); direction = 1; }
	else if (getX() > patrolMaxX) { setX(patrolMaxX); direction = -1; }

	anim.update(deltaTime);
}
