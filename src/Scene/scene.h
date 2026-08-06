#ifndef SCENE_H
#define SCENE_H

#include <SDL3/SDL.h>

class scene {

public:
    static const float SCREEN_WIDTH;
    static const float SCREEN_HEIGHT;
    static const float TILE_MAP;

 
    scene();
    virtual ~scene();

    virtual void preLoad(SDL_Renderer* renderer) = 0;

    virtual void handleInput(const SDL_Event& event) = 0;

    virtual void update(float deltaTime) = 0;

    virtual void render(SDL_Renderer* renderer) = 0;

    virtual void switchScene() = 0;
};

#endif // !SCENE_H