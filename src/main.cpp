#include <SDL3/SDL.h>
#include <iostream>

#include "../src/Scene/sceneMain.h"

int main(int argc, char* argv[])
{
   
    SDL_Init(SDL_INIT_VIDEO);
  
    SDL_Window* window = SDL_CreateWindow("Game", 1280, 720, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
   
    bool running = true;
    sceneMain thisScene = sceneMain();
    player myPlayer(100.0, 100.0, 50.0, 50.0);

    SDL_Event event;

    Uint64 last = SDL_GetTicks();

   

    thisScene.preLoad(renderer);

    
    while (running) {

    
        Uint64 now = SDL_GetTicks();
        float dt = (now - last) / 1000.0f;
        last = now;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
            else {
                thisScene.handleInput(event);
            }
            myPlayer.handleInput(event);
        }
      
        myPlayer.update(dt);

       
        myPlayer.render(renderer);
       
        thisScene.update(dt);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        thisScene.render(renderer);



        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}