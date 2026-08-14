#include "gameObject.h"

// x, y, width, height là các biến của hình chữ nhật trong thế giới game
// tạm thời đồng bộ renderRect với rect
gameObject::gameObject(double x, double y, double width, double height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;

	// tex chưa được nạp mà được gọi trong scene để nạp
	this->tex = nullptr;

	// khởi tạo hình chữ nhật trong không gian tọa độ
	rect.x = x;
	rect.y = y;
	rect.w = width;
	rect.h = height;

	// khởi tạo renderRect
	renderRect.x = rect.x;
	renderRect.y = rect.y;
	renderRect.w = rect.w;
	renderRect.h = rect.h;
}

gameObject::gameObject() {
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;

	rect.x = 0;
	rect.y = 0;
	rect.w = 0;
	rect.h = 0;

	// khởi tạo renderRect
	renderRect.x = rect.x;
	renderRect.y = rect.y;
	renderRect.w = rect.w;
	renderRect.h = rect.h;

	this->tex = nullptr;
	
}

double gameObject::getX() const {
	return x;
}

double gameObject::getY() const {
	return y;
}

SDL_FRect* gameObject::getRect() {
	return &rect;
}

double gameObject::getHeight() const {
	return height;
}

double gameObject::getWidth() const {
	return width;
}

SDL_Texture* gameObject::getTexture() const {
	return tex;
}

SDL_FRect* gameObject::getRenderRect() {
	return &renderRect;
}

void gameObject::setX(double newX) {
	x = newX;
	rect.x = x;
	udpRect();
}

void gameObject::setY(double newY) {
	y = newY;
	rect.y = y;
	udpRect();
}

void gameObject::setPosition(double newX, double newY) {
	gameObject::setX(newX);
	gameObject::setY(newY);
	udpRect();
}

void gameObject::setHeight(double newHeight) {
	height = newHeight;
	rect.h = height;
	udpRect();
}

void gameObject::setWidth(double newWidth) {
	width = newWidth;
	rect.w = width;
	udpRect();
}

void gameObject::setSize(double newWidth, double newHeight) {
	gameObject::setHeight(newHeight);
	gameObject::setWidth(newWidth);
	udpRect();
}

void gameObject::setTexture(SDL_Texture* texture) {
	tex = texture;
}

void gameObject::setRenderRect(SDL_FRect* rec) {
	renderRect = *rec;
}

void gameObject::udpRect() {
	rect.x = x;
	rect.y = y;
	rect.w = width;
	rect.h = height;
}

void gameObject::updRenderRect(const camera& cam) {
	renderRect.x = SDL_roundf(cam.xWorldToScreen(x));
	renderRect.y = SDL_roundf(cam.yWorldToScreen(y));
	renderRect.w = rect.w * cam.getScale();
	renderRect.h = rect.h * cam.getScale();
}

void gameObject::update(float deltaTime) {

}

void gameObject::render(SDL_Renderer* renderer) {

}


