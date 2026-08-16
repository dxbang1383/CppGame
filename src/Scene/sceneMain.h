#ifndef SCENE_MAIN_H
#define SCENE_MAIN_H

#include <SDL3/SDL.h>
#include <vector>
#include <iostream>

#include "scene.h"
#include "../GameObject/Player/player.h"
#include "../GameObject/Enemy/enemy.h"
#include "../GameObject/Platform/ladder.h"
#include "../GameObject/Platform/platform.h"
#include "../GameObject/Platform/decor.h"
#include "../engine/resourceManager.h"
#include "../engine/camera.h"
#include "../engine/UI/PauseMenu.h"
#include "../engine/UI/GameOverMenu.h"
#include "../Map/Map.h"

enum SceneAction {
    SCENE_NONE = 0,
    SCENE_MENU,
    SCENE_EDITOR,
    SCENE_QUIT
};

class sceneMain : public scene {
private:
    Map map = Map();
    std::vector<ladder> ladders; // sau chuyen vao map 

    const float TILE = 36.0f;
    const float W = 1280.0f, H = 720.0f;
    const int COLS = (int)(W / TILE);
    const int ROWS = (int)(H / TILE);

    bool paused = false;
    bool lost = false;
    PauseMenu pauseMenu;
    GameOverMenu gameOverMenu;
    float spawnX = 0.0f, spawnY = 0.0f;
    const float deathY = 2000.0f;
    int sceneAction = SCENE_NONE;

    void resetPlayer();

public:
    sceneMain();
    ~sceneMain() override;
    void preLoad(SDL_Renderer* renderer) override;
    void handleInput(const SDL_Event& event) override;
    void update(float deltaTime) override;
    void render(SDL_Renderer* renderer) override;
    void handleCollision(float deltaTime);
    bool overlaps(platform& p);
    bool overlapsLadder(ladder& l);
    void focusPlayer();
    void switchScene() override;

    int getSceneAction() const { return sceneAction; }
    void resetSceneAction() { sceneAction = SCENE_NONE; }
};

#endif // !SCENE_MAIN_H