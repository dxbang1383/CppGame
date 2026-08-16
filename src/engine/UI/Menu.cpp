#include "Menu.h"
#include "Text.h"
#include "../resourceManager.h"
#include "../../Scene/scene.h"

void Menu::preLoad(SDL_Renderer* renderer) {
    menuTex = resourceManager::getTexture(renderer, "menu");
}

SDL_FRect Menu::getDst() {
    float w = srcMenu.w * menuScale;
    float h = srcMenu.h * menuScale;
    return {
        (scene::SCREEN_WIDTH - w) / 2.0f,
        (scene::SCREEN_HEIGHT - h) / 2.0f,
        w,
        h
    };
}

SDL_FRect Menu::toScreen(const SDL_FRect& img) {
    SDL_FRect dst = getDst();
    return {
        dst.x + (img.x - srcMenu.x) * menuScale,
        dst.y + (img.y - srcMenu.y) * menuScale,
        img.w * menuScale,
        img.h * menuScale
    };
}

bool Menu::inside(const SDL_FRect& r, float x, float y) {
    return x >= r.x && x <= r.x + r.w
        && y >= r.y && y <= r.y + r.h;
}

void Menu::handleMouseMove(float mx, float my) {
    hovered = -1;
    for (int i = 0; i < 4; i++) {
        if (inside(toScreen(btnImg[i]), mx, my)) {
            hovered = i;
            break;
        }
    }
}

void Menu::handleClick(float mx, float my) {
    for (int i = 0; i < 4; i++) {
        if (inside(toScreen(btnImg[i]), mx, my)) {
            if (i == 0) action = MENU_PLAY;
            else if (i == 1) action = MENU_EDITOR;
            else if (i == 2) action = MENU_GUIDE;
            else action = MENU_QUIT;
            return;
        }
    }
}

void Menu::render(SDL_Renderer* renderer) {
    SDL_FRect dst = getDst();
    SDL_RenderTexture(renderer, menuTex, &srcMenu, &dst);

    for (int i = 0; i < 4; i++) {
        SDL_FRect btn = toScreen(btnImg[i]);

        float tw = 0.0f, th = 0.0f;
        Text::measure(labels[i], &tw, &th);
        if (th <= 0.0f) continue;

        float s = (btn.h * 0.7f) / th;
        float maxW = btn.w * 0.9f;
        if (tw * s > maxW) s = maxW / tw;

        float drawW = tw * s;
        float drawH = th * s;
        float x = btn.x + (btn.w - drawW) / 2.0f;
        float y = btn.y + (btn.h - drawH) / 2.0f;

        SDL_Color color = (hovered == i) ? SDL_Color{ 255, 255, 255, 255 } : SDL_Color{ 0, 0, 0, 255 };
        Text::draw(renderer, labels[i], x, y, color, s);
    }
}
