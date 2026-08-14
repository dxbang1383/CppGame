#ifndef PALETTE_H
#define PALETTE_H

#include <iostream>
#include <vector>
#include <string>
#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"
enum class TileLayer {
	LAYER_PLATFORM,
	LAYER_DECOR,
	LAYER_ENEMY
};

class Palette {
private:
	float x, y;
	float width, height;
	SDL_FRect rect;
	SDL_Texture* tex = nullptr;
	SDL_FRect texRect;
	std::string type; // type la ma map dung de cap nhat texture
	bool gridState = true; // co in grid hay khong
	TileLayer selectedLayer = TileLayer::LAYER_PLATFORM;
	int srcX, srcY;

public:
	// Constructor
	Palette(float x = 0, float y = 0, std::string type = "map1");

	// Getter / Setter
	float getX() { return x; }
	float getY() { return y; }
	float getWidth() { return width; }
	float getHeight() { return height; }
	SDL_FRect getRect() { return rect; }
	SDL_Texture* getTexture() { return tex; }
	SDL_FRect* getTexRect() { return &texRect; }
	std::string getType() { return type; }
	// trả về dạng tile được thêm 
	TileLayer getLayer() { return selectedLayer; } 
	int getSrcX() { return srcX; }
	int getSrcY() { return srcY; }

	void setLayer(TileLayer layer) { selectedLayer = layer; }
	void setX(float x) { this->x = x; }
	void setY(float y) { this->y = y; }
	void setWidth(float width) { this->width = width; }
	void setHeight(float height) { this->height = height; }
	void setRect(SDL_FRect rect) { this->rect = rect; }
	void setTexture(SDL_Texture* tex) { this->tex = tex; }
	void setTexRect(SDL_FRect texRect) { this->texRect = texRect; }
	void setType(std::string type) { this->type = type; }


	// hàm này sau này tính kích thươc palette dựa trên kích thước window
	void setSize();
	void renderGrid(SDL_Renderer* renderer);
	void render(SDL_Renderer* renderer);

	void mouseClick(int x, int y);
	void update(float deltaTime);


};

#endif // !PALETTE_H
