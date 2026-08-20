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
    howToPlayTex = resourceManager::getTexture(renderer, "howtoplay");
}

void sceneMenu::handleInput(const SDL_Event& event) {
    if (event.type == SDL_EVENT_MOUSE_MOTION) {
        if (!showHowToPlay) {
            menu.handleMouseMove(event.motion.x, event.motion.y);
        }
    }
    else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN
             && event.button.button == SDL_BUTTON_LEFT) {
        if (event.button.x >= helpBtnRect.x && event.button.x <= helpBtnRect.x + helpBtnRect.w
            && event.button.y >= helpBtnRect.y && event.button.y <= helpBtnRect.y + helpBtnRect.h) {
            showHowToPlay = !showHowToPlay;
            return;
        }

        if (settings.handleClick(event.button.x, event.button.y, 1220.0f, 20.0f)) return;

        if (!showHowToPlay) {
            menu.handleClick(event.button.x, event.button.y);
            if (menu.getAction() == MENU_GUIDE) {
                showHowToPlay = true;
                menu.resetAction();
            }
        }
    }
}

void sceneMenu::update(float deltaTime) {}

void sceneMenu::render(SDL_Renderer* renderer) {
    SDL_FRect bkgRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderTexture(renderer, bkg, nullptr, &bkgRect);

    menu.render(renderer);

    if (showHowToPlay && howToPlayTex) {
        SDL_FRect fullRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
        SDL_RenderTexture(renderer, howToPlayTex, nullptr, &fullRect);
    }

    SDL_RenderTexture(renderer, iconTex, &iconBSrc, &helpBtnRect);
    settings.render(renderer, 1220.0f, 20.0f);
}

void sceneMenu::switchScene() {}
