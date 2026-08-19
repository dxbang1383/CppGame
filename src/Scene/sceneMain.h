#ifndef SCENE_MAIN_H
#define SCENE_MAIN_H

#include <SDL3/SDL.h>
#include <vector>
#include <iostream>
#include <string>

#include "scene.h"
#include "../engine/UI/Text.h"
#include "../GameObject/Player/player.h"
#include "../GameObject/Enemy/enemy.h"
#include "../GameObject/Tile/ladder.h"
#include "../GameObject/Tile/spike.h"
#include "../GameObject/Tile/switch.h"
#include "../GameObject/Tile/platform.h"
#include "../GameObject/Tile/decor.h"
#include "../GameObject/Special/itembox.h"
#include "../GameObject/Special/item.h"
#include "../engine/resourceManager.h"
#include "../engine/camera.h"
#include "../engine/UI/PauseMenu.h"
#include "../engine/UI/GameOverMenu.h"
#include "../engine/UI/SettingsMenu.h"
#include "../GameObject/Special/coin.h"    
#include "../GameObject/Special/diamond.h"
#include "../Map/Map.h"

enum SceneAction {
    SCENE_NONE = 0,
    SCENE_MENU,
    SCENE_EDITOR,
    SCENE_QUIT
};

class sceneMain : public scene {
private:
    Map map = Map();

    //coin and diamond
    SDL_Texture* NDiamonds = nullptr;

    const float TILE = 36.0f;
    const float W = 1280.0f, H = 720.0f;
    const int COLS = (int)(W / TILE);
    const int ROWS = (int)(H / TILE);
    SDL_Texture* Icoin = nullptr;
    SDL_Texture* Ispeed = nullptr;
    SDL_Texture* Iheart = nullptr;
    SDL_Texture* Istar = nullptr;
    SDL_Texture* Inogravity = nullptr;
    SDL_Texture* Idoublejump = nullptr;
    SDL_Texture* Ihighjump = nullptr;

    Animation goalFlag{ 2, 0.3f };

    bool paused = false;
    bool lost = false;
    bool complete = false;

    // Am thanh:
    // tieng thua phat tre 2s de tieng punji/enemy keu truoc
    float loseTimer = 0.0f;
    bool loseSoundPending = false;
    float ladderSoundTimer = 0.0f;

    PauseMenu pauseMenu;
    GameOverMenu gameOverMenu;
    SettingsMenu settings;
    const float deathY = 2000.0f;

    // set = 0.5 ở player atcell
    float teleportCooldown = 0.0f;
    int sceneAction = SCENE_NONE;
    std::string mapPath;
    SDL_Renderer* gameRenderer = nullptr;

    SDL_Texture* iconTex = nullptr;
    SDL_FRect pauseIconSrc = { 545.0f, 337.0f, 40.0f, 40.0f };
    SDL_FRect resumeIconSrc = { 298.0f, 218.0f, 40.0f, 40.0f };
    SDL_FRect toggleBtnRect = { 1220.0f, 20.0f, 40.0f, 40.0f };
    SDL_FRect iconBSrc = { 397.0f, 278.0f, 40.0f, 40.0f };

    void resetGame();
    void resetPlayer();
    // Nap lai man choi
    void resetLevel();
    // Goi khi nguoi choi that su chet het mau / roi vuc
    void playerDies(bool byTrap = false);
    void renderHUD(SDL_Renderer* renderer);
    // ve co dung dua tai o dich cua man choi
    void renderGoalFlag(SDL_Renderer* renderer);

    // ---- Chuoi uu tien xu li input ----
    bool handleSettingsInput(const SDL_Event& event);
    bool handleGameOverInput(const SDL_Event& event);
    bool handlePauseToggle(const SDL_Event& event);
    bool handlePauseMenuInput(const SDL_Event& event);
    // Dieu khien nhan vat, chi chay khi khong co menu nao dang mo
    void handlePlayerInput(const SDL_Event& event);
    void handlePlayerKeyDown(SDL_Keycode key);
    void handlePlayerKeyUp(SDL_Keycode key);

public:
    sceneMain();
    void preLoad(SDL_Renderer* renderer) override;
    void handleInput(const SDL_Event& event) override;
    void update(float deltaTime) override;
    void render(SDL_Renderer* renderer) override;
    void handleCollision(float deltaTime);
    void handlePlatformCollision(float deltaTime);
    void handleItemBoxCollision(float deltaTime);
    void handleLadderCollision(float deltaTime);
    void handleSwitchCollision(float deltaTime);
    void handleSpikeCollison(float deltaTime);
    void handleItemCollison(float deltaTime);
    void handleEnemyCollision(float deltaTime);
    void handleTeleportCollision(float deltaTime);
    bool overlaps(platform& p);
    bool overlapsLadder(ladder& l);
    // kiểm tra ng chơi có ở ô này không
    bool playerAtCell(int col, int row);
    // dịch chuyển người chơi đến hàng row cột col 
    void movePlayerToCell(int col, int row);
    void checkEnd();

    void focusPlayer();
    void switchScene() override;
    void checkCollectables();
    int  getSceneAction() const { return sceneAction; }
    void resetSceneAction() { sceneAction = SCENE_NONE; }
    bool checkCollision(const gameObject& a, const gameObject& b) {
        return (a.getX() < b.getX() + b.getWidth() &&
                a.getX() + a.getWidth() > b.getX() &&
                a.getY() < b.getY() + b.getHeight() &&
                a.getY() + a.getHeight() > b.getY());
    }
};

#endif // !SCENE_MAIN_H