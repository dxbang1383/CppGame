#ifndef ENEMY_H
#define ENEMY_H

#include <SDL3/SDL.h>
#include "../src/GameObject/gameObject.h"
class enemy : public gameObject {
private:

public:
	enemy(double x, double y, double width, double height);
	enemy();

	void update(float deltaTime) override;
	void render(SDL_Renderer* renderer) override;

};

#endif // !ENEMY_H

