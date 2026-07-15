#ifndef ENEMY_H
#define ENEMY_H

#include <SDL3/SDL.h>
#include "../src/GameObject/gameObject.cpp"
class enemy : public gameObject {
private:

public:
	enemy(double x, double y, double width, double height);

};

#endif // !ENEMY_H

