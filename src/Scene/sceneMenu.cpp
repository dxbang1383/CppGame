#include "sceneMenu.h"

sceneMenu::sceneMenu() {
    menu.setScale(2.0f);
}

sceneMenu::~sceneMenu() {}

void sceneMenu::preLoad(SDL_Renderer* renderer) {
    menu.preLoad(renderer);
}

void sceneMenu::handleInput(const SDL_Event& event) {
    if (event.type == SDL_EVENT_MOUSE_MOTION) {
        menu.handleMouseMove(event.motion.x, event.motion.y);
    }
    else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN
             && event.button.button == SDL_BUTTON_LEFT) {
        menu.handleClick(event.button.x, event.button.y);
    }
}

void sceneMenu::update(float deltaTime) {}

void sceneMenu::render(SDL_Renderer* renderer) {
    menu.render(renderer);
}

void sceneMenu::switchScene() {}
