#include "sceneMain.h"

sceneMain::sceneMain()
    : mainPlayer(100.0, 100.0, 50.0, 50.0) 
{
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
}

sceneMain::~sceneMain() {

}

void sceneMain::preLoad(SDL_Renderer* renderer) {
    bkg = resourceManager::loadImage(renderer, "default");
    p1 = resourceManager::loadImage(renderer, "P");

    for (platform& x : plat) {
        if (x.getType() == "P")
            x.setTexture(p1);
    }
}

void sceneMain::handleInput(const SDL_Event& event) {
    mainPlayer.handleInput(event);
}

void sceneMain::update(float deltaTime) {
  
    mainPlayer.update(deltaTime);
    /* 
    float groundLevel = 500.0f - mainPlayer.getHeight();

    if (mainPlayer.getY() >= groundLevel) {
        mainPlayer.setY(groundLevel);      
        mainPlayer.setOnGround(true);    
    }
    else {
        mainPlayer.setOnGround(false);      
    }*/
    handleCollision();
}

void sceneMain::render(SDL_Renderer* renderer) {
    
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_FRect groundRect = { 0.0f, 500.0f, 1280.0f, 220.0f };
    SDL_RenderFillRect(renderer, &groundRect);

    SDL_FRect bkgRect = { 0, 0, 1280, 720 };
    SDL_RenderTexture(renderer, bkg, nullptr, &bkgRect);

    for (platform& p : plat)
        p.render(renderer);

    mainPlayer.render(renderer);
}

void sceneMain::handleCollision() {
    for (platform& p : plat) {
        // bien nay chi check xem co va cham khong
        bool check = mainPlayer.getX() < p.getX() + p.getWidth()
            && mainPlayer.getX() + mainPlayer.getWidth() > p.getX()
            && mainPlayer.getY() < p.getY() + p.getHeight()
            && mainPlayer.getY() + mainPlayer.getHeight() > p.getY();
        if (check == true) {
            std::cout << "co va cham nguoi choi voi platform di vao xu ly va cham" << std::endl;
            // neu va cham theo phuong thang dung
            mainPlayer.setY(p.getY() - mainPlayer.getHeight());
        }
    }
}