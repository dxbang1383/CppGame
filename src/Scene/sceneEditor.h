#ifndef SCENE_EDITOR_H
#define SCENE_EDITOR_H

#include <SDL3/SDL.h>
#include <vector>
#include <iostream>

#include "scene.h"
#include "sceneMain.h"
#include "../GameObject/Player/player.h"
#include "../GameObject/Tile/platform.h"
#include "../GameObject/Tile/decor.h"
#include "../engine/resourceManager.h"
#include "../engine/camera.h"
#include "../engine/UI/Palette.h"
#include "../engine/UI/PauseMenu.h"
#include "../engine/UI/SettingsMenu.h"
#include "../Map/Map.h"
#include "../GameObject/Tile/ladder.h"

class sceneEditor : public scene {
private:
    Map map = Map();

    Palette palette;
    SDL_Renderer* rend = nullptr;
    bool rendergrid = true;

    bool paused = false;
    PauseMenu pauseMenu;
    SettingsMenu settings;
    int sceneAction = SCENE_NONE;

    SDL_Texture* iconTex = nullptr;
    SDL_FRect pauseIconSrc = { 545.0f, 337.0f, 40.0f, 40.0f };
    SDL_FRect resumeIconSrc = { 298.0f, 218.0f, 40.0f, 40.0f };
    SDL_FRect toggleBtnRect = { 1220.0f, 20.0f, 40.0f, 40.0f };
    SDL_FRect iconBSrc = { 397.0f, 278.0f, 40.0f, 40.0f };
    SDL_Texture* howToPlayTex = nullptr;
    bool showHowToPlay = false;

    void placeAt(int col, int row);   // dat tile theo layer dang chon
    // ve mot o mau tai (col, row) - dung cho diem bat dau / ket thuc
    void renderCell(SDL_Renderer* renderer, int col, int row, SDL_Color color, const std::string& label);

public:
    sceneEditor();
    ~sceneEditor() override;
    void preLoad(SDL_Renderer* renderer) override;
    void handleInput(const SDL_Event& event) override;
    void update(float deltaTime) override;

    void render(SDL_Renderer* renderer) override;
    void switchScene() override;
    void renderGrid(SDL_Renderer* renderer);

    int getSceneAction() const { return sceneAction; }
    void resetSceneAction() { sceneAction = SCENE_NONE; }
};

#endif // !SCENE_EDITOR_H
