cmake_minimum_required(VERSION 3.20)

project(CppGame)

set(CMAKE_CXX_STANDARD 20)

add_executable(CppGame)

target_sources(CppGame PRIVATE
    src/main.cpp
    
    )

target_include_directories(CppGame PRIVATE
    SDL3/include
    src
)

target_link_directories(CppGame PRIVATE
    SDL3/lib/x64
)

target_link_libraries(CppGame PRIVATE
    SDL3
)

add_custom_command(TARGET CppGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${PROJECT_SOURCE_DIR}/SDL3/lib/x64/SDL3.dll"
    "$<TARGET_FILE_DIR:CppGame>"
)