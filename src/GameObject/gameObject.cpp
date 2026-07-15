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

double gameObject::getX() const {
	return x;
}

double gameObject::getY() const {
	return y;
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

void 

