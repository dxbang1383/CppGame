#ifndef SCENE_MENU_H
#define SCENE_MENU_H

#include <SDL3/SDL.h>
#include "scene.h"

enum MenuAction {
    MENU_NONE = 0,
    MENU_PLAY,
    MENU_EDITOR,
    MENU_GUIDE,
    MENU_QUIT
};

class sceneMenu : public scene {
private:
    SDL_Texture* menuTex = nullptr;
    int action = MENU_NONE;

    float menuScale = 1.0f;

    SDL_FRect srcMenu   = { 38.0f, 218.0f, 225.0f, 157.0f };

    SDL_FRect playImg   = { 38.0f, 220.0f, 225.0f, 30.0f };
    SDL_FRect editorImg = { 38.0f, 263.0f, 225.0f, 29.0f };
    SDL_FRect guideImg  = { 38.0f, 303.0f, 225.0f, 29.0f };
    SDL_FRect quitImg   = { 38.0f, 343.0f, 225.0f, 30.0f };

    SDL_FRect getDst();
    SDL_FRect toScreen(const SDL_FRect& img);
    bool inside(const SDL_FRect& r, float x, float y);

public:
    sceneMenu();
    ~sceneMenu() override;

    void preLoad(SDL_Renderer* renderer) override;
    void handleInput(const SDL_Event& event) override;
    void update(float deltaTime) override;
    void render(SDL_Renderer* renderer) override;
    void switchScene() override;

    void setScale(float s) { menuScale = s; }
    int getAction() const { return action; }
    void resetAction() { action = MENU_NONE; }
};

#endif
