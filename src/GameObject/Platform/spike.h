#pragma once
#ifndef SPIKE_H
#define SPIKE_H

#include <SDL3/SDL.h>
#include <string>
#include "../src/GameObject/gameObject.h"

class spike : public gameObject {
private:
    SDL_Texture* texture = nullptr;
    SDL_FRect renderRect = { 0, 0, 0, 0 };

    bool active = true; 

public:
    spike() = default;

    spike(float x, float y, float w, float h);

    void updRenderRect(const SDL_FRect& cam);
    void render(SDL_Renderer* renderer);

    bool isActive() const { return active; }
    void setActive(bool status) { active = status; }
    void setTexture(SDL_Texture* tex) { texture = tex; }
};

#endif