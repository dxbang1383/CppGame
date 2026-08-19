#ifndef FISH_H
#define FISH_H

#include "enemy.h"

class fish : public enemy {
private:
	double patrolMinY = 0.0;
	double patrolMaxY = 0.0;

	float insetSide = 6.0f;
	float insetVert = 5.0f;

public:
	fish(int col, int row, int patrol);

	void update(float deltaTime) override;
	void render(SDL_Renderer* renderer) override;

	float getInsetSide() const { return insetSide; }
	float getInsetVert() const { return insetVert; }
};

#endif // !FISH_H
