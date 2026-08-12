#ifndef SCENE_MAIN_H
#define SCENE_MAIN_H

#include <SDL3/SDL.h>
#include <vector>
#include <iostream>

#include "scene.h"
#include "../GameObject/Player/player.h"
#include "../GameObject/Enemy/enemy.h"
#include "../GameObject/Platform/platform.h"
#include "../GameObject/Platform/decor.h"
#include "../engine/resourceManager.h"
#include "../engine/camera.h"
#include "../Map/Map.h"

class sceneMain : public scene {
private:
    Map map = Map();
    const float TILE = 36.0f;
    const float W = 1280.0f, H = 720.0f;
    const int COLS = (int)(W / TILE);   // 35
    const int ROWS = (int)(H / TILE);

public:
    sceneMain();
    ~sceneMain() override;
    // Hàm load tài nguyên trước level 
    void preLoad(SDL_Renderer* renderer) override;
    void handleInput(const SDL_Event& event) override;
    void update(float deltaTime) override;
    void render(SDL_Renderer* renderer) override;
    void handleCollision(float deltaTime);
    bool overlaps(platform& p);

    void focusPlayer();
    void switchScene() override;

};

#endif // !SCENE_MAIN_H