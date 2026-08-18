#include "walker.h"

walker::walker(int col, int row, int patrol, int kind) : enemy(col, row, patrol) {
	this->kind = kind;
	type = "walker" + std::to_string(kind);
	anim = Animation(3, 0.15f);
	anim.setLoopFrames(2);

	patrolMinX = getX() - 3 * platform::TILE_SIZE;
	patrolMaxX = getX() + 3 * platform::TILE_SIZE;

	if (kind == 1) { insetSide = 4.0f; insetTop = 6.0f; }
	else if (kind == 2) { insetSide = 5.0f; insetTop = 12.0f; }
}

void walker::stop() {
	stopped = true;
	anim.freezeAt(2);
}

void walker::update(float deltaTime) {
	if (!alive) return;

	if (stopped) {
		anim.freezeAt(2);
		return;
	}

	velocityX = speed * direction;
	setX(getX() + velocityX * deltaTime);

	if (getX() < patrolMinX) { setX(patrolMinX); direction = 1; }
	else if (getX() > patrolMaxX) { setX(patrolMaxX); direction = -1; }

	anim.update(deltaTime);
}
