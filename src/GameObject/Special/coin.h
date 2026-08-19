#ifndef COIN_H
#define COIN_H

#include <SDL3/SDL.h>
#include <string>
#include <../src/GameObject/Tile/tile.h>
#include <../src/engine/Animation.h>

class Coin : public tile {
private:
    bool collected = false;
    int value = 1;
    Animation anim{ 2, 0.2f }; // Kh?i t?o Animation: 2 frame, 0.2s m?i frame

public:
    using tile::tile;

    // G�n texture cho Animation ?? n� t�nh to�n frameW, frameH
    void setTexture(SDL_Texture* tex) {
        tile::setTexture(tex);
        anim.setTexture(tex);
    }

    // C?p nh?t timer c?a animation
    void update(float deltaTime) {
        anim.update(deltaTime);
    }

    // V? coin b?ng Animation
    void render(SDL_Renderer* renderer) {
        if (collected || !getTexture()) return;

        SDL_FRect srcRect = anim.getSrcRect();
        SDL_FRect* dstRect = getRenderRect(); 

        SDL_RenderTexture(renderer, getTexture(), &srcRect, dstRect);
    }

    bool isCollected() const { return collected; }
    void setCollected(bool state) { collected = state; }
    int getValue() const { return value; }
};

#endif // !COIN_H