#include <SDL3/SDL.h>
#include <iostream>

#include "../src/Scene/sceneMain.h"

int main(int argc, char* argv[])
{
    // khởi tạo
    // ----------------------------

    SDL_Init(SDL_INIT_VIDEO);
    // Taọ cửa sổ
    SDL_Window* window = SDL_CreateWindow("Game", 1280, 720, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
   
    bool running = true;
    sceneMain thisScene = sceneMain();

    SDL_Event event;

    Uint64 last = SDL_GetTicks();

    // --------------------------------

    thisScene.preLoad(renderer);

    // vòng lặp game
    while (running) {

        // tính thời gian để giới hạn vận tốc
        Uint64 now = SDL_GetTicks();
        float dt = (now - last) / 1000.0f;
        last = now;

        // Poll event là stack các input đầu vào chờ xử lý 
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
            else {
                thisScene.handleInput(event);
            }
        }

        // Update trước khi vẽ 
        thisScene.update(dt);

        // Xóa màn hình và vẽ lại ,
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        thisScene.render(renderer);


        // Vẽ mọi thứ ra màn hình 
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}