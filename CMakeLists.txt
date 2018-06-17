cmake_minimum_required(VERSION 3.10)
project(BattleshipOpenGL)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lmingw32")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(logic/ai-engine)
include_directories(logic/game-engine)
include_directories(logic/model)

link_directories(${PROJECT_SOURCE_DIR}/lib)

set(SOURCE_FILES main.cpp)
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


TARGET_LINK_LIBRARIES(BattleshipOpenGL SDL2_image SDL2main SDL2 SDL2_ttf)