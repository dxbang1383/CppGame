#ifndef SCENE_MAIN_H
#define SCENE_MAIN_H

#include <SDL3/SDL.h>
#include <vector>
#include <iostream>

#include "scene.h"
#include "../GameObject/Player/player.h"
#include "../GameObject/Enemy/enemy.h"
#include "../GameObject/Tile/ladder.h"
#include "../GameObject/Tile/spike.h"
#include "../GameObject/Tile/switch.h"
#include "../GameObject/Tile/platform.h"
#include "../GameObject/Tile/decor.h"
#include "../GameObject/Special/itembox.h"
#include "../GameObject/Special/item.h"
#include "../engine/resourceManager.h"
#include "../engine/camera.h"
#include "../Map/Map.h"

class sceneMain : public scene {
private:
    Map map = Map();
    std::vector<ladder> ladders; // sau chuyen vao map 
    std::vector<spike> spikes;
    SDL_Texture* spikeTexture = nullptr;

    const float TILE = 36.0f;
    const float W = 1280.0f, H = 720.0f;
    const int COLS = (int)(W / TILE);
    const int ROWS = (int)(H / TILE);
    SDL_Texture* Icoin = nullptr;
    SDL_Texture* Ispeed = nullptr;
    SDL_Texture* Iheart = nullptr;
    SDL_Texture* Istar = nullptr;
    SDL_Texture* Inogravity = nullptr;
    SDL_Texture* Idoublejump = nullptr;
    SDL_Texture* Ihighjump = nullptr;

public:
    sceneMain();
    ~sceneMain() override;
    void preLoad(SDL_Renderer* renderer) override;
    void handleInput(const SDL_Event& event) override;
    void update(float deltaTime) override;
    void render(SDL_Renderer* renderer) override;
    void handleCollision(float deltaTime);
    bool overlaps(platform& p);
    bool overlapsLadder(ladder& l);
    void focusPlayer();
    void switchScene() override;
    bool checkCollision(const gameObject& a, const gameObject& b) {
        return (a.getX() < b.getX() + b.getWidth() &&
                a.getX() + a.getWidth() > b.getX() &&
                a.getY() < b.getY() + b.getHeight() &&
                a.getY() + a.getHeight() > b.getY());
    }
};

#endif // !SCENE_MAIN_H