cmake_minimum_required(VERSION 4.0)
project(game-c++)

set(CMAKE_CXX_STANDARD 14)
find_package(raylib CONFIG REQUIRED)

add_executable(game-c++
        src/coreMechanics/test.cpp
        src/coreMechanics/player.cpp
        src/coreMechanics/player.h
        src/coreMechanics/mouse.cpp
        src/coreMechanics/mouse.h
        src/coreMechanics/stats.cpp
        src/coreMechanics/stats.h
        src/coreMechanics/shoot.cpp
        src/coreMechanics/shoot.h
        src/coreMechanics/settings.cpp
        src/coreMechanics/settings.h
        src/coreMechanics/playerCamera.cpp
        src/coreMechanics/playerCamera.h
        src/main.cpp
        src/gameStates/gameState.h
        src/gameStates/startScreenState.h
        src/gameStates/gameStateManager.h
        src/gameStates/gameStateSkeleton.h
        src/gameStates/gameType.h
        src/gameStates/soloLobby.h
        src/gameStates/soloGame.h
)
target_link_libraries(game-c++ PRIVATE raylib)