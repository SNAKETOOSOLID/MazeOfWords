#include <gtest/gtest.h>
#include "Maze.h"
#include "Config.h"

TEST(MazeTest, ConstructorGeneratesPassableStart) {
    Maze maze;
    EXPECT_TRUE(maze.isPassable(1, 1));
}

TEST(MazeTest, BoundariesAreWalls) {
    Maze maze;
    EXPECT_FALSE(maze.isPassable(0, 0));
    EXPECT_FALSE(maze.isPassable(MAZE_WIDTH - 1, MAZE_HEIGHT - 1));
    EXPECT_FALSE(maze.isPassable(-1, 5));
    EXPECT_FALSE(maze.isPassable(MAZE_WIDTH, 5));
}

TEST(MazeTest, GetPassableCellsReturnsOnlyPassable) {
    Maze maze;
    auto cells = maze.getPassableCells();
    for (const auto& [x, y] : cells) {
        EXPECT_TRUE(maze.isPassable(x, y));
    }
}

TEST(MazeTest, GetPassableCellsCountIsReasonable) {
    Maze maze;
    auto cells = maze.getPassableCells();
    EXPECT_GT(cells.size(), 10);
    EXPECT_LT(cells.size(), static_cast<size_t>(MAZE_WIDTH * MAZE_HEIGHT));
}