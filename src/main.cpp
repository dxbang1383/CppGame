#include <SDL3/SDL.h>
#include <iostream>

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    // Taọ cửa sổ
    SDL_Window* window = SDL_CreateWindow("Game", 1280, 720, 0);
    //
    bool running = true;

    SDL_Event event;
    // vòng lặp game
    while (running) {
        // Poll event là stack các input đầu vào chờ xử lý 
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
            else if (event.type == SDL_EVENT_KEY_DOWN) {
                std::cout << "Nhan phim " << std :: endl;
                if (event.key.key == SDLK_A) {
                    std::cout << " A " << std :: endl;
                }
            }
        }
    }

    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}