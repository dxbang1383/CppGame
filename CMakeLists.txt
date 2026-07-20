cmake_minimum_required(VERSION 3.20)

project(CppGame)

set(CMAKE_CXX_STANDARD 20)

add_executable(CppGame)

target_sources(CppGame PRIVATE
    src/main.cpp
    
     "src/GameObject/Player/player.cpp" 
     "src/GameObject/Enemy/enemy.cpp" 
     "src/GameObject/Platform/platform.cpp" 
     "src/GameObject/Platform/staticPlatform.cpp" 
     "src/GameObject/Platform/movingPlatform.cpp" 
     "src/Scene/scene.cpp" "src/Scene/sceneMain.cpp" 
     "src/GameObject/Enemy/enemy.h" 
     "src/GameObject/Platform/movingPlatform.h" 
     "src/GameObject/Platform/platform.h" 
     "src/GameObject/Platform/staticPlatform.h" 
     "src/GameObject/Player/player.h" 
     "src/Scene/scene.h" 
     "src/Scene/sceneMain.h" 
     "src/GameObject/gameObject.cpp"  
     "src/GameObject/gameObject.h" 
     "src/engine/camera.h"
     "src/engine/camera.cpp"
     "src/engine/resourceManager.h"
     "src/engine/resourceManager.cpp"
)

target_include_directories(CppGame PRIVATE
    SDL3/include
    SDL3_image/include
    src
)

target_link_directories(CppGame PRIVATE
    SDL3/lib/x64
    SDL3_image/lib/x64
)

target_link_libraries(CppGame PRIVATE
    SDL3
    SDL3_image
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
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${PROJECT_SOURCE_DIR}/assets"
    "$<TARGET_FILE_DIR:CppGame>/assets"
)