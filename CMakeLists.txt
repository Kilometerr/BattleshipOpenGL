cmake_minimum_required(VERSION 3.10)
project(BattleshipOpenGL)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(SDL2_PATH "C:\\Users\\Kacper\\Downloads\\SDL2-2.0.8\\x86_64-w64-mingw32")
set(SDL2_DIR "C:\\Users\\Kacper\\Downloads\\SDL2_image-2.0.3\\x86_64-w64-mingw32")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR})
include_directories(logic/ai-engine)
include_directories(logic/game-engine)
include_directories(logic/model)

add_executable(BattleshipOpenGL
        logic/ai-engine/AiEngine.cpp
        logic/ai-engine/AiEngine.h
        logic/game-engine/GameEngine.cpp
        logic/game-engine/GameEngine.h
        logic/model/Game.cpp
        logic/model/Game.h
        logic/model/Player.cpp
        logic/model/Player.h
        logic/model/Point.cpp
        logic/model/Point.h
        logic/model/Ship.cpp
        logic/model/Ship.h
        main.cpp
        )


TARGET_LINK_LIBRARIES(BattleshipOpenGL ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})