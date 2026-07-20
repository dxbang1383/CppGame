#ifndef SCENEMAIN_H
#define SCENEMAIN_H

#include <SDL3/SDL.h>
#include <vector>
#include <iostream>
#include <SDL3_image/SDL_image.h>

#include "../GameObject/Platform/platform.h"
#include "../GameObject/Player/player.h"
#include "../engine/resourceManager.h"

class sceneMain {
private:
	player player01;
	std::vector<platform> plat;
	SDL_Texture* bkg;
	SDL_Texture* p1;
public: 
	// constructor
	sceneMain();
	void loadLevel();
	void preLoad(SDL_Renderer *renderer);
	void update(float deltaTime);
	void render(SDL_Renderer * renderer);
	void handleInput(SDL_Event& event);
};

#endif // !SCENEMAIN_H
