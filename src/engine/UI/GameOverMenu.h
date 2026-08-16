#ifndef GAME_OVER_MENU_H
#define GAME_OVER_MENU_H

#include <SDL3/SDL.h>
#include <string>

enum GameOverAction {
    GAMEOVER_NONE = 0,
    GAMEOVER_REPLAY,
    GAMEOVER_MODE2,
    GAMEOVER_MENU,
    GAMEOVER_QUIT
};

class GameOverMenu {
private:
    SDL_Texture* menuTex = nullptr;
    std::string labels[4] = { "Play again", "MODE 2", "Menu", "Quit" };

    int action = GAMEOVER_NONE;
    int hovered = -1;
    float menuScale = 2.0f;

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

    int getAction() const { return action; }
    void resetAction() { action = GAMEOVER_NONE; }
};

#endif
