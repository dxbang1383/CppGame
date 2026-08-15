#include "Menu.h"
#include "../resourceManager.h"
#include "../../Scene/scene.h"

void Menu::preLoad(SDL_Renderer* renderer) {
    menuTex = resourceManager::getTexture(renderer, "menu");
    labelTex[0] = resourceManager::getTexture(renderer, "label_mode1");
    labelTex[1] = resourceManager::getTexture(renderer, "label_mode2");
    labelTex[2] = resourceManager::getTexture(renderer, "label_guide");
    labelTex[3] = resourceManager::getTexture(renderer, "label_quit");
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
        if (!labelTex[i]) continue;

        SDL_FRect btn = toScreen(btnImg[i]);

        float texW = 0.0f, texH = 0.0f;
        SDL_GetTextureSize(labelTex[i], &texW, &texH);

        float s = (btn.h * 0.7f) / texH;
        float maxW = btn.w * 0.9f;
        if (texW * s > maxW) s = maxW / texW;

        float drawW = texW * s;
        float drawH = texH * s;

        SDL_FRect labelDst = {
            btn.x + (btn.w - drawW) / 2.0f,
            btn.y + (btn.h - drawH) / 2.0f,
            drawW,
            drawH
        };

        if (hovered == i) SDL_SetTextureColorMod(labelTex[i], 255, 255, 255);
        else SDL_SetTextureColorMod(labelTex[i], 0, 0, 0);

        SDL_RenderTexture(renderer, labelTex[i], nullptr, &labelDst);
    }
}
