#ifndef SCENE_MAIN_H
#define SCENE_MAIN_H

#include <SDL3/SDL.h>
#include <vector>
#include <iostream>

#include "scene.h"
#include "../GameObject/Player/player.h"
#include "../GameObject/Platform/platform.h"
#include "../engine/resourceManager.h"

class sceneMain : public scene {
private:
    player mainPlayer;
    std::vector<platform> plat;
    SDL_Texture* bkg = nullptr;
    SDL_Texture* p1 = nullptr;
    SDL_Texture* p2 = nullptr;

public:
    sceneMain();
    ~sceneMain() override;

    void preLoad(SDL_Renderer* renderer) override;
    void handleInput(const SDL_Event& event) override;
    void update(float deltaTime) override;
    void render(SDL_Renderer* renderer) override;
    void handleCollision();

};

#endif // !SCENE_MAIN_H