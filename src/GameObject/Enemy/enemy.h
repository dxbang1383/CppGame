#ifndef ENEMY_H
#define ENEMY_H

#include <SDL3/SDL.h>
#include "../src/GameObject/gameObject.cpp"
class enemy : public gameObject {
private:

public:
	enemy(int x, int y, int width, int height);

};

#endif // !ENEMY_H

