#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <SDL3_image/SDL_image.h>
#include <iostream>
#include <vector>
#include <SDL3/SDL.h>
#include <cstring>
#include <map>

class resourceManager {
private:
	static std::map<std::string, std::string> pathTable;
	static std::map<std::string, SDL_Texture*> cache;

public :
	// static SDL_Texture* loadImage(SDL_Renderer* renderer, std::string s);

	static SDL_Texture* getTexture (SDL_Renderer* renderer, const std::string& key);

	// ham nay duoc goi khi ket thuc o main 
	static void clearAll();
};

#endif 