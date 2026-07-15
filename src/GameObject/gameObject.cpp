#include "gameObject.h"

gameObject::gameObject(int x, int y, int width, int height)
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

int gameObject::getX() const {
	return x;
}

int gameObject::getY() const {
	return y;
}

int gameObject::getHeight() const {
	return height;
}

int gameObject::getWidth() const {
	return width;
}

void gameObject::setX(int newX) {
	x = newX;
	rect.x = x;
}

void gameObject::setY(int newY) {
	y = newY;
	rect.y = y;
}

void gameObject::setPosition(int newX, int newY) {
	gameObject::setX(newX);
	gameObject::setY(newY);
}

void gameObject::setHeight(int newHeight) {
	height = newHeight;
	rect.h = height;
}

void gameObject::setWidth(int newWidth) {
	width = newWidth;
	rect.w = width;
}

void gameObject::setSize(int newWidth, int newHeight) {
	gameObject::setHeight(newHeight);
	gameObject::setWidth(newWidth);
}

