#ifndef WALKER_H
#define WALKER_H

#include "enemy.h"

class walker : public enemy {
private:
	double patrolMinX = 0.0;
	double patrolMaxX = 0.0;
	bool onGround = false;

	int kind = 1;
	bool stopped = false;

	float insetSide = 0.0f;
	float insetTop = 0.0f;

public:
	walker(int col, int row, int patrol, int kind);

	void update(float deltaTime) override;

	int getKind() const { return kind; }
	bool isStopped() const { return stopped; }
	float getInsetSide() const { return insetSide; }
	float getInsetTop() const { return insetTop; }
	void stop();

	void setOnGround(bool g) { onGround = g; }
	bool isOnGround() const { return onGround; }
};

#endif // !WALKER_H
