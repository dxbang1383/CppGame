#include "sceneMenu.h"
#include "../engine/resourceManager.h"

sceneMenu::sceneMenu() {}

sceneMenu::~sceneMenu() {}

void sceneMenu::preLoad(SDL_Renderer* renderer) {
    menuTex = resourceManager::getTexture(renderer, "menu");
}

SDL_FRect sceneMenu::getDst() {
    float w = srcMenu.w * menuScale;
    float h = srcMenu.h * menuScale;
    return {
        (scene::SCREEN_WIDTH  - w) / 2.0f,
        (scene::SCREEN_HEIGHT - h) / 2.0f,
        w,
        h
    };
}

SDL_FRect sceneMenu::toScreen(const SDL_FRect& img) {
    SDL_FRect dst = getDst();
    return {
        dst.x + (img.x - srcMenu.x) * menuScale,
        dst.y + (img.y - srcMenu.y) * menuScale,
        img.w * menuScale,
        img.h * menuScale
    };
}

bool sceneMenu::inside(const SDL_FRect& r, float x, float y) {
    return x >= r.x && x <= r.x + r.w
        && y >= r.y && y <= r.y + r.h;
}

void sceneMenu::handleInput(const SDL_Event& event) {
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN
        && event.button.button == SDL_BUTTON_LEFT) {
        float mx = event.button.x;
        float my = event.button.y;

        if (inside(toScreen(playImg), mx, my))        action = MENU_PLAY;
        else if (inside(toScreen(editorImg), mx, my)) action = MENU_EDITOR;
        else if (inside(toScreen(guideImg), mx, my))  action = MENU_GUIDE;
        else if (inside(toScreen(quitImg), mx, my))   action = MENU_QUIT;
    }
}

void sceneMenu::update(float deltaTime) {}

void sceneMenu::render(SDL_Renderer* renderer) {
    SDL_FRect dst = getDst();
    SDL_RenderTexture(renderer, menuTex, &srcMenu, &dst);
}

void sceneMenu::switchScene() {}
