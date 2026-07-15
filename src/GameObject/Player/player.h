#ifndef PLAYER_H
#define PLAYER_H

#include <SDL3/SDL.h>
#include "../src/GameObject/gameObject.h"

class player : public gameObject {
private:
	double speed = 20;
public :
	// Constructor
	player(double x, double y, double width, double height);

	void setSpeed(double speed);

	void render(SDL_Renderer* renderer) override;
	void update(float deltaTime);
};

#endif // !PLAYER_H
