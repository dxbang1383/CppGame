#ifndef WALKER_H
#define WALKER_H

#include "enemy.h"

/*
	Quai duoi dat . chua lam trong luc 
	// todo
*/
class walker : public enemy {
private:
	double patrolMinX = 0.0;
	double patrolMaxX = 0.0;
	bool onGround = false;

public:
	walker(int col, int row, int patrol);

	void update(float deltaTime) override;

	void setOnGround(bool g) { onGround = g; }
	bool isOnGround() const { return onGround; }
};

#endif // !WALKER_H
