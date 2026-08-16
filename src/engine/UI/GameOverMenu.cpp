#include "GameOverMenu.h"
#include "Text.h"
#include "../resourceManager.h"
#include "../../Scene/scene.h"

void GameOverMenu::preLoad(SDL_Renderer* renderer) {
    menuTex = resourceManager::getTexture(renderer, "menu");
}

SDL_FRect GameOverMenu::getDst() {
    float w = srcMenu.w * menuScale;
    float h = srcMenu.h * menuScale;
    return {
        (scene::SCREEN_WIDTH - w) / 2.0f,
        (scene::SCREEN_HEIGHT - h) / 2.0f,
        w,
        h
    };
}

SDL_FRect GameOverMenu::toScreen(const SDL_FRect& img) {
    SDL_FRect dst = getDst();
    return {
        dst.x + (img.x - srcMenu.x) * menuScale,
        dst.y + (img.y - srcMenu.y) * menuScale,
        img.w * menuScale,
        img.h * menuScale
    };
}

bool GameOverMenu::inside(const SDL_FRect& r, float x, float y) {
    return x >= r.x && x <= r.x + r.w
        && y >= r.y && y <= r.y + r.h;
}

void GameOverMenu::handleMouseMove(float mx, float my) {
    hovered = -1;
    for (int i = 0; i < 4; i++) {
        if (inside(toScreen(btnImg[i]), mx, my)) {
            hovered = i;
            break;
        }
    }
}

void GameOverMenu::handleClick(float mx, float my) {
    for (int i = 0; i < 4; i++) {
        if (inside(toScreen(btnImg[i]), mx, my)) {
            if (i == 0) action = GAMEOVER_REPLAY;
            else if (i == 1) action = GAMEOVER_MODE2;
            else if (i == 2) action = GAMEOVER_MENU;
            else action = GAMEOVER_QUIT;
            return;
        }
    }
}

void GameOverMenu::render(SDL_Renderer* renderer) {
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
