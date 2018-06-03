cmake_minimum_required(VERSION 3.11)
project(untitled7)

set(CMAKE_CXX_STANDARD 11)

add_executable(untitled7 main.cpp game-engine/model/Player.cpp game-engine/model/Player.h game-engine/model/Ship.cpp game-engine/model/Ship.h game-engine/model/Game.cpp game-engine/model/Game.h game-engine/model/Point.cpp game-engine/model/Point.h game-engine/engine/AiEngine.cpp game-engine/engine/AiEngine.h game-engine/engine/GameEngine.cpp game-engine/engine/GameEngine.h)