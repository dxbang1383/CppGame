#include "Palette.h"
#include "Text.h"
#include "../resourceManager.h"
#include "../../GameObject/Tile/tile.h"

// ---- thong so bo cuc ----
static constexpr float BTN_X = 20.0f;    // le trai cua nut
static constexpr float BTN_W = 180.0f;   // rong nut
static constexpr float BTN_H = 52.0f;    // cao nut
static constexpr float BTN_GAP = 12.0f;  // ho giua 2 nut
static constexpr float BTN_Y0 = 74.0f;   // nut dau tien bat dau o day
static constexpr float PAD = 24.0f;      // le quanh vung noi dung

static constexpr float NAMED_CELL = 78.0f;  // canh 1 o anh roi
static constexpr float NAMED_GAP = 12.0f;   // ho giua 2 o anh roi

// So luong nut chon loai
static constexpr int CAT_COUNT = 9;


void Palette::preLoad(SDL_Renderer* renderer, float w, float h) {
	rend = renderer;
	screenW = w;
	screenH = h;

	// cot trai = le + nut + le
	sidebarW = BTN_X + BTN_W + BTN_X;

	// vung noi dung nam ben phai cot nut
	content.x = sidebarW + PAD;
	content.y = BTN_Y0;
	content.w = screenW - sidebarW - PAD * 2.0f;
	content.h = screenH - BTN_Y0 - PAD;

	sheets.clear();
	sheets.push_back("map1");
	sheets.push_back("map2");
	sheets.push_back("map3");
	sheets.push_back("map4");
	sheets.push_back("map5");
	sheets.push_back("map6");
	sheets.push_back("map7");
	sheets.push_back("map8");

	buildCategoryButtons();
	loadSheet(0);
}

// Tao 5 nut chon loai, xep doc trong cot trai
void Palette::buildCategoryButtons() {
	std::string labels[CAT_COUNT] = {
		"PLATFORM", "DECOR", "DECOR ANIM", "LADDER", "ENEMY", "SWITCH", "SPIKE", "BOX", "TELEPORT"
	};
	TileLayer layers[CAT_COUNT] = {
		TileLayer::LAYER_PLATFORM,
		TileLayer::LAYER_DECOR,
		TileLayer::LAYER_DECOR_ANIM,
		TileLayer::LAYER_LADDER,
		TileLayer::LAYER_ENEMY,
		TileLayer::LAYER_SWITCH,
		TileLayer::LAYER_SPIKE,
		TileLayer::LAYER_BOX,
		TileLayer::LAYER_TELEPORT
	};

	catBtns.clear();
	catLayers.clear();

	float y = BTN_Y0;

	for (int i = 0; i < CAT_COUNT; i++) {
		SDL_FRect box;
		box.x = BTN_X;
		box.y = y;
		box.w = BTN_W;
		box.h = BTN_H;

		catBtns.push_back(Button(box, labels[i]));
		catLayers.push_back(layers[i]);

		y = y + BTN_H + BTN_GAP;
	}

	catBtns[0].setSelected(true);
}

// Nap sheet moi va tinh lai luoi sao cho vua khung content
void Palette::loadSheet(int index) {
	if (sheets.empty()) {
		return;
	}

	activeSheet = index;
	sheetTex = resourceManager::getTexture(rend, sheets[activeSheet]);

	if (sheetTex == nullptr) {
		sheetCols = 0;
		sheetRows = 0;
		return;
	}

	float texW = 0.0f;
	float texH = 0.0f;
	SDL_GetTextureSize(sheetTex, &texW, &texH);

	sheetCols = (int)(texW / tile::TILE_MAP);
	sheetRows = (int)(texH / tile::TILE_MAP);

	if (sheetCols <= 0 || sheetRows <= 0) {
		return;
	}

	// He so phong sao cho ca sheet vua khung, van giu o vuong
	float zx = content.w / texW;
	float zy = content.h / texH;
	float zoom = 0.0f;

	if (zx < zy) {
		zoom = zx;
	}
	else {
		zoom = zy;
	}

	cell = tile::TILE_MAP * zoom;

	// can giua khung content
	float w = sheetCols * cell;
	float h = sheetRows * cell;

	sheetArea.x = content.x + (content.w - w) / 2.0f;
	sheetArea.y = content.y + (content.h - h) / 2.0f;
	sheetArea.w = w;
	sheetArea.h = h;
}

// Tu danh sach `named` dung ra luoi nut co icon
void Palette::buildNamedButtons() {
	std::cout << "buildNameButton"<< std::endl;
	namedBtns.clear();

	// số hàng tối đa chứa được 
	int perRow = (int)(content.w / (NAMED_CELL + NAMED_GAP));

	if (perRow < 1) {
		perRow = 1;
	}

	for (int i = 0; i < (int)named.size(); i++) {
		int c = i % perRow;
		int r = i / perRow;

		SDL_FRect box;
		box.x = content.x + c * (NAMED_CELL + NAMED_GAP);
		box.y = content.y + r * (NAMED_CELL + NAMED_GAP);
		box.w = NAMED_CELL;
		box.h = NAMED_CELL;

		Button b = Button(box, named[i]);
		b.setIcon(resourceManager::getTexture(rend, named[i]));

		namedBtns.push_back(b);
	}
}

// Chuyen sang man picker tuong ung voi loai vua chon
void Palette::openLayer(TileLayer l) {
	layer = l;

	// chir cho mot nut o che do selected
	for (int i = 0; i < (int)catBtns.size(); i++) {
		if (catLayers[i] == l) {
			catBtns[i].setSelected(true);
		}
		else {
			catBtns[i].setSelected(false);
		}
	}

	named.clear();

	if (l == TileLayer::LAYER_PLATFORM || l == TileLayer::LAYER_DECOR) {
		// cat o tu sheet
		texKey = sheets[activeSheet];
		mode = PaletteMode::PICK_SHEET;
		return;
	}

	if (l == TileLayer::LAYER_DECOR_ANIM) {
		named.push_back("water");
		named.push_back("waterfall_top");
		named.push_back("waterfall_mid");
		named.push_back("waterfall_bot");
		named.push_back("flag");
		mode = PaletteMode::PICK_NAMED;
	}
	else if (l == TileLayer::LAYER_LADDER) {
		named.push_back("ladder_top");
		named.push_back("ladder_down");
		mode = PaletteMode::PICK_NAMED;
	}
	else if (l == TileLayer::LAYER_ENEMY) {
		named.push_back("flyer");
		mode = PaletteMode::PICK_NAMED;
	}
	else if (l == TileLayer::LAYER_SWITCH) {
		named.push_back("switch");
		mode = PaletteMode::PICK_NAMED;
	}
	else if (l == TileLayer::LAYER_SPIKE) {
		named.push_back("spike");
		mode = PaletteMode::PICK_NAMED;
	}
	else if (l == TileLayer::LAYER_TELEPORT) {
		named.push_back("teleport");
		mode = PaletteMode::PICK_NAMED;
	}
	else if (l == TileLayer::LAYER_BOX) {
		named.push_back("box_coin");
		named.push_back("box_question");
		named.push_back("box_item");
		mode = PaletteMode::PICK_NAMED;
	}
	buildNamedButtons();
	
}

void Palette::toggle() {
	if (mode == PaletteMode::CLOSED) {
		mode = PaletteMode::PICK_CATEGORY;
	}
	else {
		mode = PaletteMode::CLOSED;
	}
}

// Doi toa do chuot thanh o (srcX, srcY) tren sheet
// thay doi truc tiep bien srcX , srcY
bool Palette::handleSheetClick(float mx, float my) {
	float x = mx - sheetArea.x;
	float y = my - sheetArea.y;

	// click ngoai sheet thi bo qua
	if (x < 0.0f || y < 0.0f || x >= sheetArea.w || y >= sheetArea.h) {
		return false;
	}

	srcX = (int)(x / cell);
	srcY = (int)(y / cell);
	texKey = sheets[activeSheet];

	return true;
}

// Tim nut nao chua chuot -> lay ten sprite lam texKey
bool Palette::handleNamedClick(float mx, float my) {
	for (size_t i = 0; i < namedBtns.size(); i++) {
		if (namedBtns[i].contains(mx, my) == false) {
			continue;
		}

		texKey = named[i];
		srcX = 0;
		srcY = 0;

		// chuyển trạng thái chọn sang tắt ở các button khác 
		for (size_t j = 0; j < namedBtns.size(); j++) {
			namedBtns[j].setSelected(false);
		} 
		// bật duy nhất 1 biêns
		namedBtns[i].setSelected(true);

		return true;
	}

	return false;
}

bool Palette::handleInput(const SDL_Event& event) {
	// palette dang dong thi khong nhan gi
	if (mode == PaletteMode::CLOSED) {
		return false;
	}

	// quơ chuột 
	if (event.type == SDL_EVENT_MOUSE_MOTION) {
		for (int i = 0; i < (int)catBtns.size(); i++) {
			catBtns[i].handleMotion(event.motion.x, event.motion.y);
		}
		for (int i = 0; i < (int)namedBtns.size(); i++) {
			namedBtns[i].handleMotion(event.motion.x, event.motion.y);
		}
		return true;
	}

	// phim key để chuyển trạng thái 
	if (event.type == SDL_EVENT_KEY_DOWN) {
		switch (event.key.key) {
		case SDLK_LEFT:
			if (mode == PaletteMode::PICK_SHEET) {
				int n = (int)sheets.size();
				loadSheet((activeSheet - 1 + n) % n);
			}
			break;

		case SDLK_RIGHT:
			if (mode == PaletteMode::PICK_SHEET) {
				int n = (int)sheets.size();
				loadSheet((activeSheet + 1) % n);
			}
			break;

		case SDLK_ESCAPE:
			mode = PaletteMode::CLOSED;
			break;
		}

		return true;   // palette dang mo thi nuot moi phim
	}

	if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN
		&& event.button.button == SDL_BUTTON_LEFT) {

		float mx = event.button.x;
		float my = event.button.y;

		// sideBar
		for (int i = 0; i < (int)catBtns.size(); i++) {
			if (catBtns[i].contains(mx, my)) {
				openLayer(catLayers[i]);
				return true;
			}
		}

		// chọn content
		if (mode == PaletteMode::PICK_SHEET) {
			handleSheetClick(mx, my);
		}
		else if (mode == PaletteMode::PICK_NAMED) {
			handleNamedClick(mx, my);
		}

		return true;   // click trong palette KHONG duoc roi xuong canvas
	}

	return true;
}

void Palette::renderSheet(SDL_Renderer* r) {
	if (sheetTex == nullptr) {
		return;
	}

	SDL_RenderTexture(r, sheetTex, nullptr, &sheetArea);

	// grid
	SDL_SetRenderDrawColor(r, 255, 255, 255, 40);

	for (int c = 0; c <= sheetCols; c++) {
		float x = sheetArea.x + c * cell;
		SDL_RenderLine(r, x, sheetArea.y, x, sheetArea.y + sheetArea.h);
	}
	for (int j = 0; j <= sheetRows; j++) {
		float y = sheetArea.y + j * cell;
		SDL_RenderLine(r, sheetArea.x, y, sheetArea.x + sheetArea.w, y);
	}

	// khung do danh dau o dang chon
	if (texKey == sheets[activeSheet]) {
		SDL_FRect sel;
		sel.x = sheetArea.x + srcX * cell;
		sel.y = sheetArea.y + srcY * cell;
		sel.w = cell;
		sel.h = cell;

		SDL_SetRenderDrawColor(r, 255, 60, 60, 255);
		SDL_RenderRect(r, &sel);
	}

	std::string info = "CURRENT: " + sheets[activeSheet] + "   <- -> SWAP TILE MAP ";
	SDL_Color white = { 220, 220, 235, 255 };
	Text::draw(r, info, content.x, content.y - 34.0f, white, 0.42f);
}

void Palette::renderNamed(SDL_Renderer* r) {
	SDL_Color grey = { 190, 190, 205, 255 };


	for (int i = 0; i < (int)namedBtns.size(); i++) {
		// VẼ Ô BUTTON
		namedBtns[i].render(r);
		// vẽ chữ phía dưới
		SDL_FRect box = namedBtns[i].getRect();
		Text::draw(r, named[i], box.x, box.y + box.h + 4.0f, grey, 0.30f);
	}
}

void Palette::render(SDL_Renderer* renderer) {
	if (mode == PaletteMode::CLOSED) {
		return;
	}

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 16, 16, 22, 232);

	SDL_FRect bg;
	bg.x = 0.0f;
	bg.y = 0.0f;
	bg.w = screenW;
	bg.h = screenH;
	SDL_RenderFillRect(renderer, &bg);

	// nèn sidebar
	SDL_SetRenderDrawColor(renderer, 26, 26, 34, 255);

	SDL_FRect side;
	side.x = 0.0f;
	side.y = 0.0f;
	side.w = sidebarW;
	side.h = screenH;
	SDL_RenderFillRect(renderer, &side);

	SDL_Color gold = { 235, 210, 120, 255 };
	Text::draw(renderer, "PALETTE", BTN_X, 22.0f, gold, 0.55f);

	for (int i = 0; i < (int)catBtns.size(); i++) {
		catBtns[i].render(renderer);
	}

	if (mode == PaletteMode::PICK_SHEET) {
		renderSheet(renderer);
	}
	else if (mode == PaletteMode::PICK_NAMED) {
		renderNamed(renderer);
	}

	// vẽ chữ 
	else {
		SDL_Color grey = { 170, 170, 185, 255 };
		Text::draw(renderer, "SELECT :",
			content.x, content.y, grey, 0.45f);
	}
}
