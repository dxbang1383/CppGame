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

    Palette palette;
    SDL_Renderer* rend = nullptr;
    bool rendergrid = true;


    void placeAt(int col, int row);   // dat tile theo layer dang chon
    // ve mot o mau tai (col, row) - dung cho diem bat dau / ket thuc
    void renderCell(SDL_Renderer* renderer, int col, int row, SDL_Color color, const std::string& label);

public :

    sceneEditor();
    ~sceneEditor() override;
    void preLoad(SDL_Renderer* renderer )override;
    void handleInput(const SDL_Event& event) override;
    void update(float deltaTime) override;

    void render(SDL_Renderer* renderer) override;
    void switchScene() override;
    void renderGrid(SDL_Renderer * renderer);
};


#endif // !SCENE_EDITOR_H
