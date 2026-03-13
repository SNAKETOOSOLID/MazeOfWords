#pragma once

constexpr int MAZE_WIDTH = 13;
constexpr int MAZE_HEIGHT = 13;
constexpr int NUM_HINTS = 6;
constexpr int MAX_SCORE = 1500;
constexpr int STEP_PENALTY = 5;
constexpr bool isMazeSizeValid() {
    return MAZE_WIDTH % 2 == 1 && MAZE_HEIGHT % 2 == 1;
}
static_assert(isMazeSizeValid(), "Maze dimensions must be odd");