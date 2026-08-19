#include "itemBox.h"

itemBox::itemBox(int col, int row, BoxType type)
	: specialObject(col, row), boxType(type)
{
	pY = 0;
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
// thay đổi cả bouncing và velocity
void itemBox::activate() {
	if (activated) {
		return;
	}

	activated = true;
	bouncing = true;

	bounceVelocity = -120.0f;
	pY = getY();
	setSrcRect({ FRAME_SIZE, 0.0f, FRAME_SIZE, FRAME_SIZE });   // doi sang khung DA MO
}

void itemBox::update(float deltaTime) {
	// chỉ update vị trí khi boucing = true;
	if (!bouncing) {
		return;
	}

	bounceVelocity = bounceVelocity + 500 * deltaTime;
	setY(getY() + bounceVelocity * deltaTime);
}

bool itemBox::isActivated() const { return activated; }
bool itemBox::isBouncing() const { return bouncing; }
BoxType itemBox::getBoxType() const { return boxType; }
// trả về giao x cua giao 2 đường chéo của ô phía trên box hiện tại 
double itemBox::getRewardX() const { return getX() + getWidth() / 2.0; }
// trả về giao y cua giao 2 đường chéo của ô phía trên box hiện tại 
double itemBox::getRewardY() const { return getY() - getHeight() / 2.0; }
