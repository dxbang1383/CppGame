#include "Text.h"

TTF_Font* Text::font = nullptr;

bool Text::init() {
    if (!TTF_Init()) return false;
    font = TTF_OpenFont("assets/fonts/arial.ttf", 48.0f);
    return font != nullptr;
}

void Text::draw(SDL_Renderer* renderer, const std::string& text,
                float x, float y, SDL_Color color, float scale) {
    if (!font || text.empty()) return;

    SDL_Surface* surf = TTF_RenderText_Blended(font, text.c_str(), 0, color);
    if (!surf) return;

    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
    float w = surf->w * scale;
    float h = surf->h * scale;
    SDL_DestroySurface(surf);

    if (!tex) return;

    SDL_FRect dst = { x, y, w, h };
    SDL_RenderTexture(renderer, tex, nullptr, &dst);
    SDL_DestroyTexture(tex);
}

void Text::measure(const std::string& text, float* w, float* h) {
    int iw = 0, ih = 0;
    if (font) TTF_GetStringSize(font, text.c_str(), 0, &iw, &ih);
    *w = (float)iw;
    *h = (float)ih;
}

void Text::quit() {
    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }
    TTF_Quit();
}
