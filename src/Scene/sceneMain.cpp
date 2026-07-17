#include "sceneMain.h"

sceneMain::sceneMain() {
	player01 = player(20, 20, 20, 20);
	platform p1 = platform(20, 50, 20, 20);
	platform p2 = platform(20, 80, 20, 20);

	plat.push_back(p1);
	plat.push_back(p2);

	bkg = nullptr;
}

void sceneMain::preLoad(SDL_Renderer* renderer) {
	bkg = IMG_LoadTexture(renderer, "assets/kenney_pixel-platformer/SampleA.png");
	if (!bkg) {
		SDL_Log("Load anh THAT BAI: %s", SDL_GetError());   // in ra lý do
	}
	SDL_SetTextureScaleMode(bkg, SDL_SCALEMODE_NEAREST);
}

void sceneMain::loadLevel() {
	
}

void sceneMain::update(float deltaTime) {
	player01.update(deltaTime);
	for (platform p : plat) {
		p.update(deltaTime);
	}
}

void sceneMain::render(SDL_Renderer *renderer) {
	SDL_FRect bkgRect = { 0, 0, 1280, 720 };
	SDL_RenderTexture(renderer, bkg, nullptr, &bkgRect);
	for (platform p : plat) {
		p.render(renderer);
	}
	player01.render(renderer);
}

void sceneMain::handleInput(SDL_Event& event) {
	if (event.type == SDL_EVENT_KEY_DOWN) {
		if (event.key.key == SDLK_A || event.key.key == SDLK_LEFT) {
			std::cout << "A / LEFT" << std::endl;
			player01.setDirection(-1);
		}
		else if (event.key.key == SDLK_D || event.key.key == SDLK_RIGHT) {
			std::cout << "D / RIGHT" << std::endl;
			player01.setDirection(1);
		}
		else if ( event.key.key == SDLK_UP 
			|| event.key.key == SDLK_W 
			|| event.key.key == SDLK_SPACE) {


		}
	}

} 