#ifndef MENU_H
#define MENU_H

#include <SDL3/SDL.h>

enum MenuAction {
    MENU_NONE = 0,
    MENU_PLAY,
    MENU_EDITOR,
    MENU_GUIDE,
    MENU_QUIT
};

class Menu {
private:
    SDL_Texture* menuTex = nullptr;
    SDL_Texture* labelTex[4] = { nullptr, nullptr, nullptr, nullptr };

    int action = MENU_NONE;
    int hovered = -1;
    float menuScale = 1.0f;

    SDL_FRect srcMenu = { 38.0f, 218.0f, 225.0f, 157.0f };
    SDL_FRect btnImg[4] = {
        { 38.0f, 220.0f, 225.0f, 30.0f },
        { 38.0f, 263.0f, 225.0f, 29.0f },
        { 38.0f, 303.0f, 225.0f, 29.0f },
        { 38.0f, 343.0f, 225.0f, 30.0f }
    };

    SDL_FRect getDst();
    SDL_FRect toScreen(const SDL_FRect& img);
    bool inside(const SDL_FRect& r, float x, float y);

public:
    void preLoad(SDL_Renderer* renderer);
    void handleMouseMove(float mx, float my);
    void handleClick(float mx, float my);
    void render(SDL_Renderer* renderer);

    void setScale(float s) { menuScale = s; }
    int getAction() const { return action; }
    void resetAction() { action = MENU_NONE; }
};

#endif
