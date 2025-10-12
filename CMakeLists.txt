cmake_minimum_required(VERSION 4.0)
project(game-c++)

set(CMAKE_CXX_STANDARD 14)
find_package(raylib CONFIG REQUIRED)

add_executable(game-c++
        game.cpp
        player.cpp
        player.h
        mouse.cpp
        mouse.h
        stats.cpp
        stats.h
        shoot.cpp
        shoot.h
        settings.cpp
        settings.h
        playerCamera.cpp
        playerCamera.h
)
target_link_libraries(game-c++ PRIVATE raylib)