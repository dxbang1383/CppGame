#ifndef PLATFORM_H
#define PLATFORM_H

#include <SDL3/SDL.h>
#include <string>
#include "../src/GameObject/gameObject.h";

class platform : public gameObject {
private:
	std::string type = "P";
public:
	const float TILE_SIZE = 48;

	platform(double x, double y, double width, double height);
	platform(int m, int n, std::string t);

	std::string getType();

	void setType(std::string t);

	void update(float deltaTime);
	void render(SDL_Renderer* renderer) override;

};

#endif // !PLATFORM_H
