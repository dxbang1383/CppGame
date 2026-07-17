#include "gameObject.h"

gameObject::gameObject(double x, double y, double width, double height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;

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

void gameObject::setX(double newX) {
	x = newX;
	rect.x = x;
}

void gameObject::setY(double newY) {
	y = newY;
	rect.y = y;
}

void gameObject::setPosition(double newX, double newY) {
	gameObject::setX(newX);
	gameObject::setY(newY);
}

void gameObject::setHeight(double newHeight) {
	height = newHeight;
	rect.h = height;
}

void gameObject::setWidth(double newWidth) {
	width = newWidth;
	rect.w = width;
}

void gameObject::setSize(double newWidth, double newHeight) {
	gameObject::setHeight(newHeight);
	gameObject::setWidth(newWidth);
}

void gameObject::update(float deltaTime) {

}

void gameObject::render(SDL_Renderer* renderer) {

}

