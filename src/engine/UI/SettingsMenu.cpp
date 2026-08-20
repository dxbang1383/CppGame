#include "SettingsMenu.h"
#include "../resourceManager.h"
#include "../soundManager.h"
#include "../../GameObject/Player/player.h"

void SettingsMenu::preLoad(SDL_Renderer* renderer) {
    menuTex = resourceManager::getTexture(renderer, "menu");
}

bool SettingsMenu::hit(float rx, float ry, float mx, float my) {
    return mx >= rx && mx <= rx + 40.0f && my >= ry && my <= ry + 40.0f;
}

bool SettingsMenu::handleClick(float mx, float my, float iconX, float iconY) {
    if (hit(iconX, iconY, mx, my)) {
        open = !open;
        if (!open) showColorBox = false;
        return true;
    }
    if (open) {
        if (hit(iconX, iconY + 50.0f, mx, my)) { soundManager::toggleMute(); return true; }
        if (hit(iconX, iconY + 100.0f, mx, my)) {
            showColorBox = !showColorBox;
            return true;
        }
        if (showColorBox && hit(iconX - 50.0f, iconY + 100.0f, mx, my)) {
            player::nextColor();
            soundManager::playEffect("click");
            return true;
        }
        if (hit(iconX, iconY + 150.0f, mx, my)) return true;
    }
    return false;
}

void SettingsMenu::render(SDL_Renderer* renderer, float iconX, float iconY) {
    SDL_FRect s = { iconX, iconY, 40.0f, 40.0f };
    SDL_RenderTexture(renderer, menuTex, &settingsSrc, &s);

    if (!open) return;

    SDL_FRect m = { iconX, iconY + 50.0f, 40.0f, 40.0f };
    SDL_FRect c = { iconX, iconY + 100.0f, 40.0f, 40.0f };
    SDL_FRect a = { iconX, iconY + 150.0f, 40.0f, 40.0f };
    SDL_RenderTexture(renderer, menuTex, &muteSrc, &m);
    SDL_RenderTexture(renderer, menuTex, &charSrc, &c);
    SDL_RenderTexture(renderer, menuTex, &achieveSrc, &a);

    if (showColorBox) {
        SDL_FRect box = { iconX - 50.0f, iconY + 100.0f, 40.0f, 40.0f };
        SDL_FRect inner = { iconX - 45.0f, iconY + 105.0f, 30.0f, 30.0f };
        SDL_Color col = player::getPlayerColor();

        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderFillRect(renderer, &box);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderRect(renderer, &box);

        SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, 255);
        SDL_RenderFillRect(renderer, &inner);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderRect(renderer, &inner);
    }

    if (soundManager::isMuted()) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderLine(renderer, m.x, m.y, m.x + m.w, m.y + m.h);
        SDL_RenderLine(renderer, m.x, m.y + 1.0f, m.x + m.w, m.y + m.h + 1.0f);
        SDL_RenderLine(renderer, m.x + 1.0f, m.y, m.x + m.w + 1.0f, m.y + m.h);
    }
}
