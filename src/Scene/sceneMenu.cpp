#include "sceneMenu.h"
#include "../engine/resourceManager.h"

sceneMenu::sceneMenu() {
    menu.setScale(2.0f);

}

sceneMenu::~sceneMenu() {}

void sceneMenu::preLoad(SDL_Renderer* renderer) {
    menu.preLoad(renderer);
    settings.preLoad(renderer);
    iconTex = resourceManager::getTexture(renderer, "menu");
    bkg = resourceManager::getTexture(renderer, "bkg");
}

void sceneMenu::handleInput(const SDL_Event& event) {
    if (event.type == SDL_EVENT_MOUSE_MOTION) {
        menu.handleMouseMove(event.motion.x, event.motion.y);
    }
    else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN
             && event.button.button == SDL_BUTTON_LEFT) {
        if (settings.handleClick(event.button.x, event.button.y, 1220.0f, 20.0f)) return;
        menu.handleClick(event.button.x, event.button.y);
    }
}

void sceneMenu::update(float deltaTime) {}

void sceneMenu::render(SDL_Renderer* renderer) {
    SDL_FRect bkgRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderTexture(renderer, bkg, nullptr, &bkgRect);

    menu.render(renderer);

    SDL_FRect rb = { 1170.0f, 20.0f, 40.0f, 40.0f };
    SDL_RenderTexture(renderer, iconTex, &iconBSrc, &rb);
    settings.render(renderer, 1220.0f, 20.0f);

    
}

void sceneMenu::switchScene() {}
