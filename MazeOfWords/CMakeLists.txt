cmake_minimum_required(VERSION 3.10)

project(MazeOfWords)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

set(SOURCES
        src/main.cpp
        src/ConsoleUtils.cpp
        src/Game.cpp
        src/Maze.cpp
        src/WordManager.cpp
)
add_executable(MazeOfWords ${SOURCES})