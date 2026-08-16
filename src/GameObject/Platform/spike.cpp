#include "spike.h"

spike::spike(float x, float y, float w, float h)
    : gameObject(x, y, w, h)
{
}


void spike::updRenderRect(const SDL_FRect& cam) {
    renderRect.x = getX() - cam.x;
    renderRect.y = getY() - cam.y;
    renderRect.w = getWidth();
    renderRect.h = getHeight();
}

void spike::render(SDL_Renderer* renderer) {
    if (active && texture) {
        SDL_RenderTexture(renderer, texture, NULL, &renderRect);
    }
}