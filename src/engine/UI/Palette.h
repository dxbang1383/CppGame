#ifndef PALETTE_H
#define PALETTE_H

#include <SDL3/SDL.h>
#include <string>
#include <vector>

#include "Button.h"

// dùng để addEnemy ...
enum class TileLayer {
	LAYER_PLATFORM,
	LAYER_DECOR,
	LAYER_DECOR_ANIM,
	LAYER_LADDER,
	LAYER_ENEMY,
	LAYER_SWITCH,
	LAYER_SPIKE,
	LAYER_BOX,
	LAYER_TELEPORT,
	LAYER_COIN,
	LAYER_DIAMOND
};

/*
	Ba man hinh cua palette:
	  PICK_CATEGORY : cot nut ben trai 
	  PICK_SHEET : duyet sheet map1..map8
	  PICK_NAMED : danh sach anh roi 
*/
enum class PaletteMode {
	CLOSED, 
	PICK_CATEGORY,
	PICK_SHEET,
	PICK_NAMED
};

class Palette {
private:
	float screenW = 1280.0f, screenH = 720.0f;
	// độ rộng sìdeBar ( category)
	float sidebarW = 0.0f;
	// phần bên phải để vẽ 
	SDL_FRect content{ 0.0f, 0.0f, 0.0f, 0.0f };

	PaletteMode mode = PaletteMode::CLOSED; // trạng thái của palette
	TileLayer layer = TileLayer::LAYER_PLATFORM; // addPlatform.... là lớp được chọn để lần sau thêm vào map

	std::string texKey = "map1"; // biên chonj texture để vẽ 
	int srcX = 0, srcY = 0; // src

	std::vector<Button> catBtns; // danh sách nút bấm của sidebar
	std::vector<TileLayer> catLayers; // 

	std::vector<std::string> sheets; // danh sách các key map 
	int activeSheet = 0; // map nào đang được xem 
	SDL_Texture* sheetTex = nullptr; // texture của sheet hiện tại 
	int sheetCols = 0, sheetRows = 0; // sheet có bao nhiêu ô 
	float cell = 0.0f; // kich thuoc 1 o khi hien thi
	SDL_FRect sheetArea{ 0.0f, 0.0f, 0.0f, 0.0f }; // giống renderRect là hcn nọi vẽ sheet sau khi căn chỉnh 

	// danh sách animation và ảnh rời như ladder 
	std::vector<std::string> named;
	// các nút tương ứng với ảnh 
	std::vector<Button> namedBtns;

	SDL_Renderer* rend = nullptr;

	void buildCategoryButtons(); // tạo các nút trong category ( bên trái )

	// khi nhấn vào các nút như decor , platform ...
	// chọn và lấy ra ảnh đúng như mình mong muốn ( sheet map , animation ...)
	void openLayer(TileLayer l); 
	// nạp texture cho sheet mới dùng để in ra màn hình 
	// tính lại zoom , phần để in ra màn hình cho hợp lý 
	void loadSheet(int index);
	// từ tên các ảnh và animation dựng các nút cho ng chơi bấm 
	// xử lý in sao cho xuống hàng hợp lys
	void buildNamedButtons();

	// đổi tọa độ chuột nhấn thành srcX srcY 
	// false nếu click ra ngoài 
	bool handleSheetClick(float mx, float my);
	// kiểm tra xem nút animation , ảnh rời nào đưucj click 
	// false nếu không có 
	bool handleNamedClick(float mx, float my);

	void renderSheet(SDL_Renderer* r);
	void renderNamed(SDL_Renderer* r);

public:
	// căn lề cho btn
	static constexpr float BTN_X = 20.0f;
	static constexpr float BTN_W = 180.0f;

	static constexpr float BTN_H = 44.0f;
	// kc trên dưới 2btn
	static constexpr float BTN_GAP = 10.0f;
	// dọa độ y của btn đaafu tiên 
	static constexpr float BTN_Y0 = 74.0f;
	// căn lề cho content
	static constexpr float PAD = 24.0f;

	// độ rộng của cell ảnh động hoặc ảnh rời 
	static constexpr float NAMED_CELL = 78.0f;
	static constexpr float NAMED_GAP = 12.0f;

	// load 
	void preLoad(SDL_Renderer* renderer, float w, float h);

	// tắt / bâtj palette
	void toggle();

	void close() { mode = PaletteMode::CLOSED; }
	bool isOpen() const { 
		if (mode == PaletteMode::CLOSED) {
			return false;
		}
		else return true;
	}

	bool handleInput(const SDL_Event& event);

	void render(SDL_Renderer* renderer);

	TileLayer getLayer() const { return layer; }
	const std::string& getTexKey() const { return texKey; }
	int getSrcX() const { return srcX; }
	int getSrcY() const { return srcY; }

	void setLayer(TileLayer l) { openLayer(l); }
};

#endif // !PALETTE_H
