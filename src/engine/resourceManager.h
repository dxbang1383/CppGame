#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <SDL3_image/SDL_image.h>
#include <iostream>
#include <vector>
#include <SDL3/SDL.h>
#include <cstring>

class resourceManager {

public :
	static SDL_Texture* loadImage(SDL_Renderer* renderer, std::string s);

};

#endif // !RESOURCEMANAGER_H
