#ifndef TILE_H
#define TILE_H

#include <SDL3/SDL.h>
#include <string>
#include "../gameObject.h"

/*
	Lop co so cho moi o vuong tren luoi.
	Giu vung cat tren sprite sheet (srcRect) va toa do o.
*/
class tile : public gameObject {
private:
	std::string type = "Tile";
	SDL_FRect srcRect = { 0.0f, 0.0f, 0.0f, 0.0f }; // vung cat tren sheet

public:
	static constexpr float TILE_SIZE = 36; // kich thuoc 1 o trong THE GIOI
	static constexpr float TILE_MAP = 18; // kich thuoc 1 o GOC trong sheet

	tile(double x, double y, double width, double height);
	tile(int m, int n, std::string t);
	tile(int m, int n, std::string t, int srcX, int srcY);

	std::string getType() { return type; }
	void setType(std::string t) { type = t; }
	void setSrcRect(SDL_FRect rect) { srcRect = rect; }

	int getCol() { return floor(getX()) / TILE_SIZE; }
	int getRow() { return floor(getY()) / TILE_SIZE; }
	int getSrcX() { return srcRect.x / TILE_MAP; }
	int getSrcY() { return srcRect.y / TILE_MAP; }

	void render(SDL_Renderer* renderer) override;
};

#endif // !TILE_H
