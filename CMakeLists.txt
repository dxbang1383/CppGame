cmake_minimum_required(VERSION 3.20)

project(CppGame)

set(CMAKE_CXX_STANDARD 20)

add_executable(CppGame)

target_sources(CppGame PRIVATE
    src/main.cpp
    
     "src/GameObject/Player/player.cpp"
     "src/GameObject/Enemy/enemy.cpp"
     "src/GameObject/Tile/tile.cpp"
     "src/GameObject/Tile/tile.h"
     "src/GameObject/Tile/platform.h"
     "src/GameObject/Tile/decor.cpp"
     "src/GameObject/Tile/decor.h"
     "src/GameObject/Tile/ladder.h"
     "src/GameObject/Tile/switch.h"
     "src/GameObject/Tile/spike.h"
     "src/GameObject/Special/itemBox.cpp"
     "src/GameObject/Special/itemBox.h"
     "src/GameObject/Special/item.cpp"
     "src/GameObject/Special/item.h"
     "src/Scene/scene.cpp" "src/Scene/sceneMain.cpp"
     "src/GameObject/Enemy/enemy.h"
     "src/GameObject/Player/player.h"
     "src/Scene/scene.h"
     "src/Scene/sceneMain.h"
     "src/GameObject/gameObject.cpp"
     "src/GameObject/gameObject.h"
     "src/engine/camera.h"
     "src/engine/camera.cpp"
     "src/engine/resourceManager.h"
     "src/engine/resourceManager.cpp"
     "src/Scene/sceneEditor.cpp" 
     "src/Scene/sceneEditor.h" 
     "src/engine/UI/Button.h"
     "src/engine/UI/Button.cpp"
     "src/engine/UI/Palette.h"
     "src/engine/UI/Palette.cpp" 
     "src/engine/UI/Menu.h"
     "src/engine/UI/Menu.cpp"
     "src/engine/UI/Text.h"
     "src/engine/UI/Text.cpp"
     "src/engine/UI/PauseMenu.h"
     "src/engine/UI/PauseMenu.cpp"
     "src/engine/UI/GameOverMenu.h"
     "src/engine/UI/GameOverMenu.cpp"
     "src/engine/UI/SettingsMenu.h"
     "src/engine/UI/SettingsMenu.cpp"
     "src/engine/soundManager.h"
     "src/engine/soundManager.cpp"
     "src/Map/Map.cpp" 
     "src/Map/Map.h"
     "src/engine/Animation.h"
     "src/engine/Animation.cpp"
     "src/GameObject/Enemy/flyer.h"
     "src/GameObject/Enemy/flyer.cpp"
     "src/GameObject/Enemy/walker.h"
     "src/GameObject/Enemy/walker.cpp")

target_include_directories(CppGame PRIVATE
    SDL3/include
    SDL3_image/include
    SDL3_ttf/include
    src
)

target_link_directories(CppGame PRIVATE
    SDL3/lib/x64
    SDL3_image/lib/x64
    SDL3_ttf/lib/x64
)

target_link_libraries(CppGame PRIVATE
    SDL3
    SDL3_image
    SDL3_ttf
)

add_custom_command(TARGET CppGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${PROJECT_SOURCE_DIR}/SDL3/lib/x64/SDL3.dll"
    "$<TARGET_FILE_DIR:CppGame>"
)

add_custom_command(TARGET CppGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${PROJECT_SOURCE_DIR}/SDL3_image/lib/x64/SDL3_image.dll"
    "$<TARGET_FILE_DIR:CppGame>"
)

add_custom_command(TARGET CppGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${PROJECT_SOURCE_DIR}/SDL3_ttf/lib/x64/SDL3_ttf.dll"
    "$<TARGET_FILE_DIR:CppGame>"
)

add_custom_command(TARGET CppGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${PROJECT_SOURCE_DIR}/assets"
    "$<TARGET_FILE_DIR:CppGame>/assets"
)

target_compile_definitions(CppGame PRIVATE PROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}")