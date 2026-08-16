#ifndef SWITCH_H
#define SWITCH_H

#include <SDL3/SDL.h>
#include "../src/GameObject/gameObject.h"

class Switch : public gameObject {
private:
	SDL_Texture* texture = nullptr;
	SDL_FRect renderRect = { 0, 0, 0, 0 };
	SDL_FRect srcRect = { 0, 0 ,0 ,0 };
	bool isActivated = false;
	float frameWidth = 0.0f;

	SDL_Texture* switchTexture = nullptr;


public:
	Switch(float x, float y, float w, float h, SDL_Texture* texture = nullptr);

	void setTexture(SDL_Texture* tex);
	void trigger();

	void updRenderRect(const SDL_FRect& cam);
	bool getIsActivated() const { return isActivated; }

	void render(SDL_Renderer* renderer);
};
#endif // !SWITCH_H
