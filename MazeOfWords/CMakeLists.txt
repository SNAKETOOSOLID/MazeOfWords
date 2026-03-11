cmake_minimum_required(VERSION 3.10)
project(MazeOfWords)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(MazeOfWords
        src/main.cpp
        src/ConsoleUtils.cpp
        src/Maze.cpp
        src/WordManager.cpp
        src/Game.cpp
)