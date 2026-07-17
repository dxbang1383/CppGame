#ifndef PLATFORM_H
#define PLATFORM_H

#include<SDL3/SDL.h>
#include "../src/GameObject/gameObject.h";

class platform : public gameObject {
private:

public:
	platform(double x, double y, double width, double height);

	void update(float deltaTime);
	void render(SDL_Renderer* renderer) override;

};

#endif // !PLATFORM_H
