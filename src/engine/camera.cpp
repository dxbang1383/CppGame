#include "camera.h"

float camera::getX() const {
	return x;
}

float camera::getY() const {
	return y;
}

float camera::getScale() const {
	return scale;
}

void camera::setPosition(float nx, float ny) {
	x = nx;
	y = ny;
}

void camera::setScale(float s) {
	scale = s;
}

void camera::zoomIn() {
	scale = scale * 1.05f;
	
}

void camera::zoomOut() {
	scale = scale / 1.05f;
}

void camera::focus(float drawX, float drawY, float screenW, float screenH) {
	x = drawX - screenW / (2.0f * scale);
	y = drawY - screenH / (2.0f * scale);
}

void camera::getInfo() {
	std::cout << "Camera :(" << x <<
		"," << y << ") scale = " << scale;
	std::cout << std::endl;
}

void camera::moveLeft() {
	x = x - 5;
}

void camera::moveRight() {
	x = x + 5;
}

void camera::moveUp() {
	y = y - 5;
}

void camera::moveDown() {
	y = y + 5;
}

float camera::xWorldToScreen(float xWorld) const {
	float res = xWorld * this->getScale() - this->getX() * this->getScale();
	return res;
}

float camera::yWorldToScreen(float yWorld) const {
	float res = yWorld * getScale() - getY() * getScale();
	return res;
}

float camera::xScreenToWorld(float xS) const {
	float res = (xS + getX() * getScale()) / getScale();
	return res;
}

float camera::yScreenToWorld(float yS) const {
	float res = (yS + getY() * getScale()) / getScale();
	return res;
}