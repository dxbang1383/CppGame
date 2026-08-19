    #ifndef TEXT_H
#define TEXT_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

class Text {
private:
    static TTF_Font* font;

public:
    static bool init();
    static void draw(SDL_Renderer* renderer, const std::string& text,
                     float x, float y, SDL_Color color, float scale = 1.0f);
    static void measure(const std::string& text, float* w, float* h);
    static void quit();
};

#endif
