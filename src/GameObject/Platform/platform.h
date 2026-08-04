#ifndef PLATFORM_H
#define PLATFORM_H

#include <SDL3/SDL.h>
#include <string>
#include "../src/GameObject/gameObject.h"
#include <vector>

class platform : public gameObject {
private:
	std::string type = "P";
	SDL_FRect srcRect = { 0.0f, 0.0f, 0.0f, 0.0f };
	bool animationEnable = false;
	float timeFrame = 0.25f;
	float time = 0.0f;
	int frame = 1;
	std::string typeFrame = "";
public:
	const float TILE_SIZE = 36;
	const float TILE_MAP = 18;

	platform(double x, double y, double width, double height);
	platform(int m, int n, std::string t);
	platform(int m, int n, std::string t, int srcX, int srcY);
	platform(int m, int n, std::string t, int srcX, int srcY, std::string typeAni);

	std::string getType();

	void setType(std::string t);
	void setSrcRect(SDL_FRect rect) {
		srcRect = rect;
	}

	void update(float deltaTime);
	void render(SDL_Renderer* renderer) override;

};

#endif // !PLATFORM_H
