#include "sceneEditor.h"
#include <cmath>

sceneEditor::sceneEditor() {

}

// Destruction 
sceneEditor::~sceneEditor() {

}

void sceneEditor::preLoad(SDL_Renderer* renderer) {
    rend = renderer;
    palette.preLoad(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    map.addTextures(renderer);
    map.load(std::string(PROJECT_SOURCE_DIR) + "/assets/maps/level1.txt");
}

// dat tile theo layer dang chon trong palette
void sceneEditor::placeAt(int col, int row) {
    const std::string& key = palette.getTexKey();

    switch (palette.getLayer()) {
    case TileLayer::LAYER_PLATFORM:
        map.addPlatform(col, row, key, palette.getSrcX(), palette.getSrcY());
        break;
    case TileLayer::LAYER_DECOR:
        map.addDecor(col, row, key, palette.getSrcX(), palette.getSrcY());
        break;
    case TileLayer::LAYER_DECOR_ANIM:
        map.addDecorAnim(col, row, key);
        break;
    case TileLayer::LAYER_LADDER:
        map.addLadder(col, row, key);
        break;
    case TileLayer::LAYER_ENEMY:
        map.addFlyer(col, row, 1);
        break;
    }
}

// cập nhật mỗi vòng lặp
void sceneEditor::update(float deltaTime) {

    // cập nhật vị trí trong thế giới
    for (platform& x : map.getPlatforms()) x.update(deltaTime);
    for (decor& d : map.getDecors()) d.update(deltaTime);
    for (ladder& l : map.getLadders()) l.update(deltaTime);

    // Camera chốt vị trí

    // rồi mới tính lại renderRect cho mọi object
    for (platform& x : map.getPlatforms()) x.updRenderRect(map.getCam());
    for (decor& d : map.getDecors()) d.updRenderRect(map.getCam());
    for (ladder& l : map.getLadders()) l.updRenderRect(map.getCam());
    for (flyer& f : map.getFlyers()) f.updRenderRect(map.getCam());
    for (walker& w : map.getWalkers()) w.updRenderRect(map.getCam());
}

// in ra bên ngoài 
void sceneEditor::render(SDL_Renderer* renderer) {
    //std::cout << "ground :" << mainPlayer.isOnGround() << std::endl;
    //map.getCam().getInfo();

    // dong nay them tam de add tai nguyeen 
    // ---------------------------------------------------------------------------------------------jlll

    SDL_FRect bkgRect = { 0, 0, 1280, 720 };
    SDL_RenderTexture(renderer, map.getBkg(), nullptr, &bkgRect);

    for (platform& p : map.getPlatforms()) p.render(renderer);
    for (ladder& l : map.getLadders()) l.render(renderer);
    for (decor& d : map.getDecors()) d.render(renderer);

    for (flyer& f : map.getFlyers()) f.render(renderer);
    for (walker& w : map.getWalkers()) w.render(renderer);

    if (rendergrid == true) {
        renderGrid(renderer);
    }

    palette.render(renderer);   // tu thoat neu dang dong
}

// xử lý input của scene này
void sceneEditor::handleInput(const SDL_Event& event) {

    // ---- Tab: bat/tat palette. Xu li TRUOC moi thu khac ----
    if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_TAB) {
        palette.toggle();
        return;
    }

    // ---- Palette dang mo thi no chiem toan bo input ----
    if (palette.handleInput(event)) return;

    // ---- Tu day tro xuong la canvas ----
    if (event.type == SDL_EVENT_KEY_DOWN) {
        switch (event.key.key) {
        case SDLK_A:
        case SDLK_LEFT:   map.getCam().moveLeft();  break;
        case SDLK_D:
        case SDLK_RIGHT:  map.getCam().moveRight(); break;
        case SDLK_W:
        case SDLK_UP:     map.getCam().moveUp();    break;
        case SDLK_S:
        case SDLK_DOWN:   map.getCam().moveDown();  break;

        case SDLK_F3:     rendergrid = !rendergrid; break;

        case SDLK_L:
            if (map.save(std::string(PROJECT_SOURCE_DIR) + "/assets/maps/level1.txt"))
                SDL_Log("Da luu map");
            break;
        }
    }
    else if (event.type == SDL_EVENT_MOUSE_WHEEL) {
        if (event.wheel.y > 0)      map.getCam().zoomIn();
        else if (event.wheel.y < 0) map.getCam().zoomOut();
    }
    else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        int col = map.xScreenToCol(event.button.x);
        int row = map.yScreenToRow(event.button.y);

        if (event.button.button == SDL_BUTTON_LEFT) {
            placeAt(col, row);
        }
        else if (event.button.button == SDL_BUTTON_RIGHT) {
            map.eraseAt(col, row, palette.getLayer());
        }
    }
}

void sceneEditor::switchScene() {
    //sau nay khoi tao nhan sk ban phim 
}

void sceneEditor::renderGrid(SDL_Renderer * renderer) {
    // chon mau
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    // ve Grid 
    int colS = map.getCam().getX() / (TILE_MAP * map.getCam().getScale());
    int colE = (map.getCam().getX() + SCREEN_WIDTH) / (TILE_MAP * map.getCam().getScale());

    int rowS = map.getCam().getY() / (TILE_MAP * map.getCam().getScale());
    int rowE = (map.getCam().getY() + SCREEN_HEIGHT) / (TILE_MAP * map.getCam().getScale());

    for (int i = colS; i <= colE + 1; i++) {
        // kẻ đường thẳng đứng 
        SDL_RenderLine(renderer
            , i * TILE_MAP * map.getCam().getScale() - map.getCam().getX() * map.getCam().getScale(), 0
            , i * TILE_MAP * map.getCam().getScale() - map.getCam().getX() * map.getCam().getScale(), SCREEN_HEIGHT);
    }

    for (int j = rowS; j <= rowE; j++) {
        // ke duong ngang
        SDL_RenderLine(renderer
            , 0, j * TILE_MAP * map.getCam().getScale() - map.getCam().getY() * map.getCam().getScale()
            , SCREEN_WIDTH, j * TILE_MAP * map.getCam().getScale() - map.getCam().getY() * map.getCam().getScale());
    }

}

