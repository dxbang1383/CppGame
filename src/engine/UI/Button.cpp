#include "Button.h"
#include "Text.h"

void Button::render(SDL_Renderer* renderer) const {
	if (renderer == nullptr) return;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	// Nen: dam hon khi dang chon, sang hon khi re chuot len
	if (selected)     SDL_SetRenderDrawColor(renderer, 70, 95, 130, 255);
	else if (hovered) SDL_SetRenderDrawColor(renderer, 60, 60, 72, 255);
	else              SDL_SetRenderDrawColor(renderer, 38, 38, 46, 255);
	SDL_RenderFillRect(renderer, &rect);

	// Vien sang leen khi co hove
	if (selected)     SDL_SetRenderDrawColor(renderer, 235, 200, 90, 255);
	else if (hovered) SDL_SetRenderDrawColor(renderer, 180, 180, 195, 255);
	else              SDL_SetRenderDrawColor(renderer, 100, 100, 115, 255);
	SDL_RenderRect(renderer, &rect);

	if (icon != nullptr) {
		
		if (iconSrc.w == 0.0f || iconSrc.h == 0.0f)
			SDL_RenderTexture(renderer, icon, nullptr, &rect);      // ca anh
		else
			SDL_RenderTexture(renderer, icon, &iconSrc, &rect);     // mot o tren sheet
		return;
	}

	if (label.empty()) return;

	// Can chu vao giua nut
	float tw = 0.0f, th = 0.0f;
	Text::measure(label, &tw, &th);

	float scale = 0.42f;
	tw *= scale;
	th *= scale;

	SDL_Color color;

	if (selected) {
		color = SDL_Color{ 255, 235, 150, 255 };
	}
	else {
		color = SDL_Color{ 225, 225, 235, 255 };
	}

	Text::draw(renderer, label,
		rect.x + (rect.w - tw) * 0.5f,
		rect.y + (rect.h - th) * 0.5f,
		color, scale);
}
