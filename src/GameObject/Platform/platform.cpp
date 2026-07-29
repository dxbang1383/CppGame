#include "platform.h"

platform::platform(double x, double y, double width, double height) 
	: gameObject(x, y, width, height)
{

}

// Constructor theo dia chi map 
platform::platform(int m, int n, std::string type) {\
	// Set hình chữ nhật để in 
	setX(m * TILE_SIZE);
	setY(n * TILE_SIZE);
	setWidth(TILE_SIZE);
	setHeight(TILE_SIZE);
	// 
	setType(type);
}

// khởi tạo được gán theo sprite sheet.
platform::platform(int m, int n, std::string type, int srcX, int srcY) {
	// hình chữ nhật là địa chỉ trên scene 
	setX(m * TILE_SIZE);
	setY(n * TILE_SIZE);
	setWidth(TILE_SIZE);
	setHeight(TILE_SIZE);

	// hình chữ nhật địa chỉ hình vẽ trên sheet 
	srcRect = { srcX * TILE_MAP, srcY * TILE_MAP, TILE_MAP, TILE_MAP };

	setType(type);
}

// khởi tạo có animation.
platform::platform(int m, int n, std::string type, int srcX, int srcY, std::string animationType) {
	// hình chữ nhật là địa chỉ trên scene 
	setX(m * TILE_SIZE);
	setY(n * TILE_SIZE);
	setWidth(TILE_SIZE);
	setHeight(TILE_SIZE);

	// hình chữ nhật địa chỉ hình vẽ trên sheet 
	srcRect = { srcX * TILE_MAP, srcY * TILE_MAP, TILE_MAP, TILE_MAP };

	setType(type);

	typeFrame = animationType;

	animationEnable = true;
}

std::string platform::platform::getType() {
	return type;
}

void platform::setType(std::string t) {
	this->type = t;
}

void platform::render(SDL_Renderer *renderer) {
	if (srcRect.w == 0 || srcRect.h == 0) 
	{
		SDL_RenderTexture(renderer, getTexture(), nullptr, getRenderRect());
	}
	else 
	{
		SDL_FRect temp = srcRect;

		if (animationEnable == true) {
			
			if (frame == 1) {
				// chon hinh chu nhat mac dinh
			}
			else {
				if (typeFrame == "x++") {
					temp.x = temp.x + TILE_MAP;
				}
				else if (typeFrame == "y++") {
					temp.y = temp.y + TILE_MAP;
				}
			}
		}

		SDL_RenderTexture(renderer, getTexture(), &temp, getRenderRect());
	}
}

void platform::update(float deltaTime) {
	if (animationEnable == false) return;

	time = deltaTime + time;
	
	if (time >= 0.25f) {
		if (frame == 1) frame = 2;
		else frame = 1;
		time = 0.0f;
	}
	
}