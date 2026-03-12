cmake_minimum_required(VERSION 3.10)

project(MazeOfWords)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(MazeOfWords/include)

set(SOURCES
        MazeOfWords/src/main.cpp
        MazeOfWords/src/ConsoleUtils.cpp
        MazeOfWords/src/Game.cpp
        MazeOfWords/src/Maze.cpp
        MazeOfWords/src/WordManager.cpp
)
add_executable(MazeOfWords ${SOURCES})