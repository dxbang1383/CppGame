#ifndef SCENE_EDITOR_H
#define SCENE_EDITOR_H

#include <SDL3/SDL.h>
#include <vector>
#include <iostream>

#include "scene.h"
#include "../GameObject/Player/player.h"
#include "../GameObject/Tile/platform.h"
#include "../GameObject/Tile/decor.h"
#include "../engine/resourceManager.h"
#include "../engine/camera.h"
#include "../engine/UI/Palette.h"
#include "../Map/Map.h"
#include "../GameObject/Tile/ladder.h"

class sceneEditor : public scene {
private:
    Map map = Map();

    Palette tileMap = Palette(50, 50);
    SDL_Renderer* rend = nullptr;
    int  idMap = 1;
    bool menuOpen = false;
    bool pauseMenu = false;
    bool rendergrid = true;

public :

    sceneEditor();
    ~sceneEditor() override;
    void preLoad(SDL_Renderer* renderer )override;
    void handleInput(const SDL_Event& event) override;
    void update(float deltaTime) override;

    void render(SDL_Renderer* renderer) override;
    void switchScene() override;
    void renderGrid(SDL_Renderer * renderer);
    void renderPalette(SDL_Renderer* renderer);
};


#endif // !SCENE_EDITOR_H
