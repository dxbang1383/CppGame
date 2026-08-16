#ifndef ENEMY_H
#define ENEMY_H

#include <SDL3/SDL.h>
#include <string>
#include <iostream>
#include "../src/GameObject/gameObject.h"
#include "../src/GameObject/Platform/platform.h"
#include "../src/engine/Animation.h"

/*
	Lop co so cho moi loai quai.
	Lop con tu gan "type" trong constructor de doc ghi file.
*/
class enemy : public gameObject {
protected:
	double velocityX = 0.0;
	double velocityY = 0.0;
	double speed = 120.0;
	int direction = 1;
	bool alive = true;

	std::string type;      // flyer / walker1234 duoc gan theo lop con 
	int patrol = 0;     // quy dao di chuyen 

	Animation anim;

public:
	enemy() = default;
	enemy(int col, int row, int patrol);

	virtual ~enemy() = default;

	void setTexture(SDL_Texture* tex) { anim.setTexture(tex); }

	// lop con se co update khasc nhau o cac patrol va class con
	void update(float deltaTime) override = 0;
	
	// ham nay duoc dinh nghia luon o enemy 
	void render(SDL_Renderer* renderer) override;

	const std::string& getType() const { return type; }
	int getPatrol() const { return patrol; }

	int getCol() const { return (int)(getX() / platform::TILE_SIZE); }
	int getRow() const { return (int)(getY() / platform::TILE_SIZE); }

	int  getDirection() const { return direction; }
	void turnAround() { direction = -direction; }

	bool isAlive() const { return alive; }
	void kill() { alive = false; }
};

#endif // !ENEMY_H
