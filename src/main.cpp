#include <SDL3/SDL.h>
#include <iostream>

#include "../src/Scene/sceneMenu.h"
#include "../src/Scene/sceneMain.h"
#include "../src/Scene/sceneEditor.h"
#include "../src/engine/soundManager.h"
#include "../src/engine/UI/Text.h"

int main(int argc, char* argv[])
{
    // Khoi tao sdl
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    SDL_Window* window = SDL_CreateWindow("Game", scene::SCREEN_WIDTH, scene::SCREEN_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);

    soundManager::init();
    Text::init();

    // Bien vong lap
    bool running = true;
    bool musicOn = false;

    // 
    sceneMenu menuScene = sceneMenu();
    sceneMain mainScene = sceneMain();
    sceneEditor editorScene = sceneEditor();

    scene *thisScene = &menuScene;

    SDL_Event event;
    
    Uint64 last = SDL_GetTicks();
    
    // Khoi tao scene
    menuScene.preLoad(renderer);
    mainScene.preLoad(renderer);
    editorScene.preLoad(renderer);
    
    while (running) {    
        Uint64 now = SDL_GetTicks();
        float dt = (now - last) / 1000.0f;
        last = now;
      
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }

            else {
                if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN
                    && event.button.button == SDL_BUTTON_LEFT) {
                    soundManager::playEffect("click");
                }

                if (event.type == SDL_EVENT_KEY_DOWN) {
                    if (event.key.key == SDLK_F1) { thisScene = &mainScene;   continue; }
                    if (event.key.key == SDLK_F2) { thisScene = &editorScene; continue; }
                }

                thisScene->handleInput(event);
            }
        }

        if (thisScene == &menuScene) {
            int a = menuScene.getAction();
            if (a == MENU_PLAY)        { thisScene = &mainScene;   menuScene.resetAction(); }
            else if (a == MENU_EDITOR) { thisScene = &editorScene; menuScene.resetAction(); }
            else if (a == MENU_QUIT)   { running = false; }
            else if (a == MENU_GUIDE)  { menuScene.resetAction(); }
        }

        if (thisScene == &mainScene) {
            int a = mainScene.getSceneAction();
            if (a == SCENE_MENU)        { thisScene = &menuScene; mainScene.resetSceneAction(); }
            else if (a == SCENE_EDITOR) { thisScene = &editorScene; mainScene.resetSceneAction(); }
            else if (a == SCENE_QUIT)   { running = false; }
        }

        bool inGame = (thisScene == &mainScene || thisScene == &editorScene);
        if (inGame && !musicOn) { soundManager::playMusic("bgm"); musicOn = true; }
        else if (!inGame && musicOn) { soundManager::stopMusic(); musicOn = false; }

        // update vi tri chuan bi in ra man
        thisScene->update(dt);

        soundManager::update();

        // xoa man hinh cu
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);    

        // ve map moi
        thisScene->render(renderer);

        // hien thi
        SDL_RenderPresent(renderer);

        // gioi han 60 fps
        const Uint64 targetFrameTime = 1000 / 60;
        Uint64 frameTime = SDL_GetTicks() - now;
        if (frameTime < targetFrameTime) {
            SDL_Delay((Uint32)(targetFrameTime - frameTime));
        }

    }

    soundManager::clearAll();
    Text::quit();

    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}