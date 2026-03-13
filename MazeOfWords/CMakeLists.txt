cmake_minimum_required(VERSION 3.29)
project(MazeOfWords)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

set(LIB_SOURCES
        src/ConsoleUtils.cpp
        src/Game.cpp
        src/Maze.cpp
        src/WordManager.cpp
)

add_library(MazeOfWordsLib STATIC ${LIB_SOURCES})

add_executable(MazeOfWords src/main.cpp)

target_link_libraries(MazeOfWords PRIVATE MazeOfWordsLib)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(MazeOfWordsTests
        tests/test_main.cpp
        tests/test_wordmanager.cpp
        tests/test_maze.cpp
        tests/test_game.cpp
        tests/test_entity.cpp
        tests/test_multiplicationquestion.cpp
)

target_link_libraries(MazeOfWordsTests PRIVATE MazeOfWordsLib gtest_main)

include(GoogleTest)
gtest_discover_tests(MazeOfWordsTests)