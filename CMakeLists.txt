cmake_minimum_required(VERSION 3.10)
project(BattleshipOpenGL)

set(CMAKE_CXX_STANDARD 11)

include_directories(Engine)
include_directories(Engine/Graphics)
include_directories(Engine/Graphics/SOIL/src)
include_directories(Engine/IO)
include_directories(logic/ai-engine)
include_directories(logic/game-engine)
include_directories(logic/model)

add_executable(BattleshipOpenGL
        .idea/BattleshipOpenGL.iml
        .idea/misc.xml
        .idea/modules.xml
        .idea/workspace.xml
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
        CMakeLists.txt
        main.cpp
        )
