#include "sceneEditor.h"
#include <cmath>

sceneEditor::sceneEditor() {

}

// Destruction 
sceneEditor::~sceneEditor() {

}

void sceneEditor::preLoad(SDL_Renderer* renderer) {
    tileMap.setTexture(resourceManager::getTexture(renderer, tileMap.getType()));
    map.addTextures(renderer);
    map.load(std::string(PROJECT_SOURCE_DIR) + "/assets/maps/level1.txt");
}

// cập nhật mỗi vòng lặp 
void sceneEditor::update(float deltaTime) {

    tileMap.update(deltaTime);
    // cập nhật vị trí trong thế giới
    for (platform& x : map.getPlatforms()) x.update(deltaTime);
    for (decor& d : map.getDecors()) d.update(deltaTime);

    // Camera chốt vị trí

    // rồi mới tính lại renderRect cho mọi object
    for (platform& x : map.getPlatforms()) x.updRenderRect(map.getCam());
    for (decor& d : map.getDecors()) d.updRenderRect(map.getCam());
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

    for (platform& p : map.getPlatforms())
        p.render(renderer);

    for (decor& d : map.getDecors()) {
        d.render(renderer);
    }

    for (flyer& f : map.getFlyers()) f.render(renderer);
    for (walker& w : map.getWalkers()) w.render(renderer);

    if (rendergrid == true) {
        renderGrid(renderer);
    }

    if (menuOpen == true) {
        renderPalette(renderer);
    }
    
}

// xử lý input của scene này 
void sceneEditor::handleInput(const SDL_Event& event) {

    // xử lý input trong game 
    if (menuOpen == false) {
        if (event.type == SDL_EVENT_KEY_DOWN) {
            switch (event.key.key) {
            case SDLK_A:
            case SDLK_LEFT:
                map.getCam().moveLeft();
                break;
            case SDLK_D:
            case SDLK_RIGHT:
                map.getCam().moveRight();
                break;
            case SDLK_SPACE:
            case SDLK_W:
            case SDLK_UP:
                map.getCam().moveUp();
                break;

            case SDLK_S:
            case SDLK_DOWN:
                map.getCam().moveDown();
                break;

            case SDLK_TAB:
                menuOpen = true;
                break;
                break;
            case SDLK_F3:
                rendergrid = !rendergrid;
                break;
            }

        }
        else if (event.type == SDL_EVENT_KEY_UP) {
            switch (event.key.key) {
            case SDLK_A:
            case SDLK_LEFT:
                //mainPlayer.setMovingLeft(false);
                break;
            case SDLK_D:
            case SDLK_RIGHT:
                //mainPlayer.setMovingRight(false);
                break;
            }
        }
        else if (event.type == SDL_EVENT_MOUSE_WHEEL) {
            if (event.wheel.y > 0)
            {
                // Lăn lên
                map.getCam().zoomIn();
            }
            else if (event.wheel.y < 0)
            {
                // Lăn xuống
                map.getCam().zoomOut();
            }
        }

        else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
            float mouseClickX = event.button.x;
            float mouseClickY = event.button.y;

            int col = map.xScreenToCol(mouseClickX);
            int row = map.yScreenToRow(mouseClickY);

            if (event.button.button == SDL_BUTTON_LEFT) {
                TileLayer layer = tileMap.getLayer();

                if (layer == TileLayer::LAYER_PLATFORM) {
                    map.addPlatform(col, row, tileMap.getType(),
                        tileMap.getSrcX(), tileMap.getSrcY());
                }
                else if (layer == TileLayer::LAYER_DECOR) {
                    // "-" = decor tinh
                    map.addDecor(col, row, tileMap.getType(),
                        tileMap.getSrcX(), tileMap.getSrcY(), "-");
                }
                else if (layer == TileLayer::LAYER_ENEMY) {
                    map.addFlyer(col, row, 1);
                }
            }

            else if (event.button.button == SDL_BUTTON_RIGHT) {
                std::cout << "Nhan chuot phai: " << mouseClickX << " " << mouseClickY << std::endl;
                
                if (map.eraseAt(col, row, tileMap.getLayer())) {
                    std::cout << "xoa 1 tile" << std::endl;
                }
                else {
                    std::cout << "Khong xoa gi ca" << std::endl;
                }
            }

        }
    }

    // xử lý input palette
    else if (menuOpen == true) {
        if (event.type == SDL_EVENT_KEY_DOWN) {
            switch (event.key.key) {
            case SDLK_TAB:
                menuOpen = false;
                break;
            case SDLK_F3:
                rendergrid = !rendergrid;
                break;
            case SDLK_L:
                map.save(std::string(PROJECT_SOURCE_DIR) + "/assets/maps/level1.txt");
                break;
            case SDLK_1:
                tileMap.setLayer(TileLayer::LAYER_PLATFORM);
                std::cout << "p -" << std::endl;
                break;
            case SDLK_2:
                tileMap.setLayer(TileLayer::LAYER_DECOR);
                std::cout << "d -" << std::endl;
                break;
            case SDLK_3:
                tileMap.setLayer(TileLayer::LAYER_ENEMY);
                std::cout << "e 1" << std::endl;
                break;
            }
        }
        else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                float mouseClickX = event.button.x;
                float mouseClickY = event.button.y;

                std::cout << "Nhan chuot trai: " << mouseClickX << " " << mouseClickY << std::endl;
                tileMap.mouseClick(mouseClickX, mouseClickY);
            }
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

void sceneEditor::renderPalette(SDL_Renderer* renderer) {
    // bong mo 
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200); // Alpha = 200 / 255

    SDL_FRect rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderFillRect(renderer, &rect);

    // in hinh anh tile map 

    tileMap.render(renderer);
    
}