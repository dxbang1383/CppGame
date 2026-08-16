#ifndef SETTINGS_MENU_H
#define SETTINGS_MENU_H

#include <SDL3/SDL.h>

class SettingsMenu {
private:
    SDL_Texture* menuTex = nullptr;
    bool open = false;

    SDL_FRect settingsSrc = { 347.0f, 337.0f, 40.0f, 40.0f };
    SDL_FRect muteSrc = { 347.0f, 277.0f, 40.0f, 40.0f };
    SDL_FRect charSrc = { 495.0f, 337.0f, 40.0f, 40.0f };
    SDL_FRect achieveSrc = { 495.0f, 278.0f, 40.0f, 40.0f };

    bool hit(float rx, float ry, float mx, float my);

public:
    void preLoad(SDL_Renderer* renderer);
    bool handleClick(float mx, float my, float iconX, float iconY);
    void render(SDL_Renderer* renderer, float iconX, float iconY);
    void close() { open = false; }
    bool isOpen() const { return open; }
};

#endif
