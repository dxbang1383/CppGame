#ifndef SCENE_MENU_H
#define SCENE_MENU_H

#include <SDL3/SDL.h>
#include "scene.h"
#include "../engine/UI/Menu.h"
#include "../engine/UI/SettingsMenu.h"

class sceneMenu : public scene {
private:
    Menu menu;
    SettingsMenu settings;

    SDL_Texture* iconTex = nullptr;
    SDL_FRect iconBSrc = { 397.0f, 278.0f, 40.0f, 40.0f };

public:
    sceneMenu();
    ~sceneMenu() override;

    void preLoad(SDL_Renderer* renderer) override;
    void handleInput(const SDL_Event& event) override;
    void update(float deltaTime) override;
    void render(SDL_Renderer* renderer) override;
    void switchScene() override;

    int getAction() const { return menu.getAction(); }
    void resetAction() { menu.resetAction(); }
};

#endif
