#include "sceneEditor.h"

sceneEditor::sceneEditor() {

    plat.emplace_back(3, 13, "map1", 2, 4);
    plat.emplace_back(4, 12, "map1", 2, 4);
    plat.emplace_back(5, 11, "map1", 2, 4);
    plat.emplace_back(6, 10, "map1", 2, 4);
}

// Destruction 
sceneEditor::~sceneEditor() {

}

void sceneEditor::preLoad(SDL_Renderer* renderer) {
    rend = renderer;
    // Backgrond
    bkg = resourceManager::getTexture(renderer, "bkg");

    // platform
    for (platform& x : plat) {
        x.setTexture(resourceManager::getTexture(renderer, x.getType()));
    }

    for (decor& d : decorList) {
        d.setTexture(resourceManager::getTexture(renderer, d.getType()));
    }

    tileMap.setTexture(resourceManager::getTexture(renderer, tileMap.getType()));

    // mainPlayer.setTexture(resourceManager::getTexture(renderer, "player"));
}

// cập nhật mỗi vòng lặp 
void sceneEditor::update(float deltaTime) {

    tileMap.update(deltaTime);
    // cập nhật vị trí trong thế giới
    for (platform& x : plat) x.update(deltaTime);
    for (decor& d : decorList) d.update(deltaTime);

    // camera chốt vị trí

    // rồi mới tính lại renderRect cho mọi object
    for (platform& x : plat) x.updRenderRect(cam);
    for (decor& d : decorList) d.updRenderRect(cam);
}

// in ra bên ngoài 
void sceneEditor::render(SDL_Renderer* renderer) {
    //std::cout << "ground :" << mainPlayer.isOnGround() << std::endl;
    //cam.getInfo();

    // dong nay them tam de add tai nguyeen 
    // ---------------------------------------------------------------------------------------------jlll
    plat[plat.size() - 1].setTexture(resourceManager::getTexture(renderer, plat[plat.size() - 1].getType()));

    SDL_FRect bkgRect = { 0, 0, 1280, 720 };
    SDL_RenderTexture(renderer, bkg, nullptr, &bkgRect);

    for (platform& p : plat)
        p.render(renderer);

    for (decor& d : decorList) {
        d.render(renderer);
    }

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
                cam.moveLeft();
                break;
            case SDLK_D:
            case SDLK_RIGHT:
                cam.moveRight();
                break;
            case SDLK_SPACE:
            case SDLK_W:
            case SDLK_UP:
                cam.moveUp();
                break;

            case SDLK_S:
            case SDLK_DOWN:
                cam.moveDown();
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
                cam.zoomIn();
            }
            else if (event.wheel.y < 0)
            {
                // Lăn xuống
                cam.zoomOut();
            }
        }
        else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                float mouseClickX = event.button.x;
                float mouseClickY = event.button.y;

                std::cout << "Nhan chuot trai: " << mouseClickX << " " << mouseClickY << std::endl;

                int convertX = cam.xScreenToWorld(mouseClickX) / platform::TILE_SIZE;
                int convertY = cam.yScreenToWorld(mouseClickY) / platform::TILE_SIZE;

                    std::cout << "Chuyen ve (x,y) trong he toa do la :"
                    << convertX
                    << " " << convertY << std::endl;
                    if (tileMap.getTypeTile() == 1) {
                        plat.emplace_back(convertX, convertY, tileMap.getType(), tileMap.getSrcX(), tileMap.getSrcY());
                        plat.back().setTexture(resourceManager::getTexture(rend, tileMap.getType()));
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
            }
        }
        else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                float mouseClickX = event.button.x;
                float mouseClickY = event.button.y;

                std::cout << "Nhan chuot trai: " << mouseClickX << " " << mouseClickY << std::endl;
                tileMap.mouseClick(mouseClickX, mouseClickY);
            }
            else if (event.button.button == SDL_BUTTON_RIGHT) {
                float mouseClickX = event.button.x;
                float mouseClickY = event.button.y;

                std::cout << "Nhan chuot phai: " << mouseClickX << " " << mouseClickY << std::endl;

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
    int colS = cam.getX() / (TILE_MAP * cam.getScale());
    int colE = (cam.getX() + SCREEN_WIDTH) / (TILE_MAP * cam.getScale());

    int rowS = cam.getY() / (TILE_MAP * cam.getScale());
    int rowE = (cam.getY() + SCREEN_HEIGHT) / (TILE_MAP * cam.getScale());

    for (int i = colS; i <= colE + 1; i++) {
        // kẻ đường thẳng đứng 
        SDL_RenderLine(renderer
            , i * TILE_MAP * cam.getScale() - cam.getX() * cam.getScale(), 0
            , i * TILE_MAP * cam.getScale() - cam.getX() * cam.getScale(), SCREEN_HEIGHT);
    }

    for (int j = rowS; j <= rowE; j++) {
        // ke duong ngang
        SDL_RenderLine(renderer
            , 0, j * TILE_MAP * cam.getScale() - cam.getY() * cam.getScale()
            , SCREEN_WIDTH, j * TILE_MAP * cam.getScale() - cam.getY() * cam.getScale());
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