#include "gameObject.h"

gameObject::gameObject(double x, double y, double width, double height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->tex = nullptr;

	rect.x = x;
	rect.y = y;
	rect.w = width;
	rect.h = height;

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

void gameObject::udpRect() {
	rect.x = x;
	rect.y = y;
	rect.w = width;
	rect.h = height;
}

void gameObject::update(float deltaTime) {

}



void gameObject::render(SDL_Renderer* renderer) {

}

