#ifndef PLAYER_H
#define PLAYER_H

#include <SDL3/SDL.h>
#include "../src/GameObject/gameObject.h"

class player : public gameObject {
private:
	const int speed = 20;
public :
	// Constructor
	player(int x, int y, int width, int height);
};

#endif // !PLAYER_H
