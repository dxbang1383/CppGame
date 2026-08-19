#include "itemBox.h"

itemBox::itemBox(int col, int row, BoxType type)
	: specialObject(col, row), boxType(type)
{
}

// Khung trai = chua mo. activate() se doi sang khung phai.
void itemBox::setTexture(SDL_Texture* tex) {
	gameObject::setTexture(tex);
	if (tex == nullptr) return;
	// khởi tạo là ở khung hình thứ nhất
	setSrcRect({ 0.0f, 0.0f, FRAME_SIZE, FRAME_SIZE });
}

// hàm này chuyển trạng thái sang active 
// frame sang ô thứ 2
void itemBox::activate() {
	if (activated) {
		return;
	}
	activated = true;
	bouncing = true;
	setSrcRect({ FRAME_SIZE, 0.0f, FRAME_SIZE, FRAME_SIZE });   // doi sang khung DA MO
}

void itemBox::update(float deltaTime) {
	if (!bouncing) {
		return;
	}

	bounceOffset += bounceVelocity * deltaTime;

	bounceVelocity += 500.0f * deltaTime;

	if (bounceOffset >= 0.0f) {
		bounceOffset = 0.0f;
		bounceVelocity = 0.0f;
		bouncing = false;
	}
}

bool itemBox::isActivated() const { return activated; }
bool itemBox::isBouncing() const { return bouncing; }
BoxType itemBox::getBoxType() const { return boxType; }

double itemBox::getRewardX() const { return getX() + getWidth() / 2.0; }
double itemBox::getRewardY() const { return getY() - getHeight() / 2.0; }
