#ifndef FLYER_H
#define FLYER_H

#include "enemy.h"

// flyer khong anh huong boi trong luc
class flyer : public enemy {
private:
	// tam thoi tien lui 
	double patrolMinX = 0.0;
	double patrolMaxX = 0.0;

public:
	flyer(int col, int row, int patrol);

	void update(float deltaTime) override;
};

#endif // !FLYER_H
