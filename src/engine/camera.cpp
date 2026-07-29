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
	scale = scale + 0.05f;
}

void camera::zoomOut() {
	scale = scale - 0.05f;
}

void camera::focus(float drawX, float drawY, float screenW, float screenH) {
	x = drawX - screenW / (2.0f * scale);
	y = drawY - screenH / (2.0f * scale);
}