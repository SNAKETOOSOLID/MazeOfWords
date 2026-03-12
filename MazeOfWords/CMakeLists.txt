cmake_minimum_required(VERSION 3.29)
project(MazeOfWords)

set(CMAKE_CXX_STANDARD 17)

add_executable(MazeOfWords
        src/main.cpp
        src/ConsoleUtils.cpp
        src/Game.cpp
        src/Maze.cpp
        src/WordManager.cpp
)