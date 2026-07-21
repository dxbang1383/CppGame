#ifndef SCENE_MAIN_H
#define SCENE_MAIN_H

#include "scene.h"
#include "../GameObject/Player/player.h"

class sceneMain : public scene {
private:
    player mainPlayer;

public:
    sceneMain();
    ~sceneMain() override;

    void preLoad(SDL_Renderer* renderer) override;
    void handleInput(const SDL_Event& event) override;
    void update(float deltaTime) override;
    void render(SDL_Renderer* renderer) override;
};

#endif // !SCENE_MAIN_H