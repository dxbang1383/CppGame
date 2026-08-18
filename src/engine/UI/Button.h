#ifndef BUTTON_H
#define BUTTON_H

#include <SDL3/SDL.h>
#include <string>

class Button {
private:
	SDL_FRect rect{ 0.0f, 0.0f, 0.0f, 0.0f }; // hcn vẽ 
	std::string label;

	SDL_Texture* icon = nullptr;
	SDL_FRect iconSrc = { 0.0f, 0.0f, 0.0f, 0.0f };   // w == 0 -> ve ca anh

	bool hovered = false; // trạng thái chuột có ở ô button này không
	bool selected = false; 

public:
	Button() = default;
	// Constructor chi can dia hcn ve button va label 
	Button(SDL_FRect r, std::string l) {
		rect = r;
		label = l;
	}
	// vị trí kichs thước hcn vẽ 
	void setRect(SDL_FRect r) { rect = r; }
	void setLabel(std::string l) { label = l; }
	// hàm để thêm texture và vị trí vẽ texture
	void setIcon(SDL_Texture* t, SDL_FRect src = {0.0, 0.0, 0.0, 0.0}) {
		icon = t;
		iconSrc = src;
	}
	void setSelected(bool s) { selected = s; }

	const SDL_FRect& getRect() const { return rect; }
	const std::string& getLabel() const { return label; }
	bool isSelected() const { return selected; }

	// dùng để kiểm tra xem chuột có trong button này không 
	// trả về true nếu có 
	bool contains(float mx, float my) const {
		return mx >= rect.x && mx < rect.x + rect.w
			&& my >= rect.y && my < rect.y + rect.h;
	}
	// điều chỉnh biến hoverd để render 
	void handleMotion(float mx, float my) { hovered = contains(mx, my); }

	void render(SDL_Renderer* renderer) const;
};

#endif // !BUTTON_H
