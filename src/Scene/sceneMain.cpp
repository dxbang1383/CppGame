#include "sceneMain.h"

// constructor
sceneMain::sceneMain() {
	player01 = player(20, 20, 20, 20);

	// Sample Map
	for (int x = 0; x < 26; x++)
		plat.emplace_back(x, 14, "P");

	plat.emplace_back(3, 13, "P");
	plat.emplace_back(4, 12, "P");
	plat.emplace_back(5, 11, "P");
	plat.emplace_back(6, 10, "P");

	for (int x = 6; x <= 12; x++)
		plat.emplace_back(x, 10, "P");

	plat.emplace_back(13, 9, "P");
	plat.emplace_back(14, 8, "P");
	plat.emplace_back(15, 7, "P");

	for (int x = 15; x <= 21; x++)
		plat.emplace_back(x, 7, "P");

	plat.emplace_back(22, 8, "P");
	plat.emplace_back(23, 9, "P");
	plat.emplace_back(24, 10, "P");

	for (int x = 21; x <= 25; x++)
		plat.emplace_back(x, 11, "P");


	bkg = nullptr;
	p1 = nullptr;
}

// tải trước các gói tài nguyên trước khi vào game 
void sceneMain::preLoad(SDL_Renderer* renderer) {
	bkg = resourceManager::loadImage(renderer, "default");
	p1 = resourceManager::loadImage(renderer, "P");

	for (platform &x : plat) {
		if (x.getType() == "P") {
			x.setTexture(p1);
			std::cout << "da load p1" << std::endl;
		}
	}
}

// load tài nguyên vào scene 
void sceneMain::loadLevel() {
	
}

// gọi mỗi vòng lặp để update vị trí 
void sceneMain::update(float deltaTime) {
	player01.update(deltaTime);
	for (platform &p : plat) {
		p.update(deltaTime);
	}
}

// Gọi hàm render của các đối tượng 
void sceneMain::render(SDL_Renderer *renderer) {
	SDL_FRect bkgRect = { 0, 0, 1280, 720 };
	SDL_RenderTexture(renderer, bkg, nullptr, &bkgRect);
	for (platform &p : plat) {
		p.render(renderer);
	}
	player01.render(renderer);
}

// xử lý input 
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