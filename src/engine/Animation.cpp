#include "Animation.h"

Animation::Animation(int frameCount, float frameTime) {
	// chan 0 va so am de an toan cho phep chia va phep % ben duoi
	this->frameCount = (frameCount > 0) ? frameCount : 1;
	this->frameTime = frameTime;
	this->loopFrames = this->frameCount;
}

void Animation::setTexture(SDL_Texture* tex) {
	texture = tex;
	if (texture == nullptr) return;

	float texW = 0.0f, texH = 0.0f;
	SDL_GetTextureSize(texture, &texW, &texH);

	// cac frame xep ngang trong 1 file nen chieu cao frame = chieu cao anh
	frameW = texW / frameCount;
	frameH = texH;
}

void Animation::update(float deltaTime) {
	if (frozen)            return;
	if (loopFrames <= 1)   return;
	if (frameTime <= 0.0f) return;

	timer += deltaTime;
	// dung while de animation duoi kip khi deltaTime vot len bat thuong
	while (timer >= frameTime) {
		timer -= frameTime;
		currentFrame = (currentFrame + 1) % loopFrames;
	}
}

void Animation::reset() {
	currentFrame = 0;
	timer = 0.0f;
}

SDL_FRect Animation::getSrcRect() const {
	return { currentFrame * frameW, 0.0f, frameW, frameH };
}
