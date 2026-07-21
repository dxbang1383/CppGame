#include "sceneMain.h"

sceneMain::sceneMain()
    : mainPlayer(100.0, 100.0, 50.0, 50.0) 
{
}

sceneMain::~sceneMain() {
}

void sceneMain::preLoad(SDL_Renderer* renderer) {
}

void sceneMain::handleInput(const SDL_Event& event) {
    mainPlayer.handleInput(event);
}

void sceneMain::update(float deltaTime) {
  
    mainPlayer.update(deltaTime);

    float groundLevel = 500.0f - mainPlayer.getHeight();

    if (mainPlayer.getY() >= groundLevel) {
        mainPlayer.setY(groundLevel);      
        mainPlayer.setOnGround(true);    
    }
    else {
        mainPlayer.setOnGround(false);      
    }
}

void sceneMain::render(SDL_Renderer* renderer) {
    
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_FRect groundRect = { 0.0f, 500.0f, 1280.0f, 220.0f };
    SDL_RenderFillRect(renderer, &groundRect);

 
    mainPlayer.render(renderer);
}