#ifndef PLAYER_H
#define PLAYER_H

#include <SDL3/SDL.h>
#include "../src/GameObject/gameObject.h"

class player : public gameObject {

private:

	double velocityX = 30.0;
	double velocityY = 0.0;
	double speed = 300.0;
	int direction = 1;
	double gravity = 300.0;
	double jumpForce = 500.0;
	bool onGround = false;

public :
	// Constructor
	player(double x, double y, double width, double height);
	player();
	// get
	int getDirection();

	// set 
	void setSpeed(double speed);
	void setDirection(int d);
		 
	// core
	void render(SDL_Renderer* renderer) override;
	void update(float deltaTime) override;
};

#endif // !PLAYER_H
