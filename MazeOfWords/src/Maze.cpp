#include "../include/Maze.h"
#include "../include/Config.h"

#include <algorithm>

Maze::Maze() : cells_(MAZE_HEIGHT, std::vector<bool>(MAZE_WIDTH, false)) {
    generate();
}

bool Maze::inBoundsCell(int x, int y) const {
    return x > 0 && x < MAZE_WIDTH - 1 && y > 0 && y < MAZE_HEIGHT - 1;
}

void Maze::addFrontier(int x, int y,
                       std::vector<Cell>& frontier,
                       std::vector<std::vector<bool>>& inFrontier,
                       const std::vector<std::vector<bool>>& visited) {
    const int dx[4] = {2, -2, 0, 0};
    const int dy[4] = {0, 0, 2, -2};

    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (inBoundsCell(nx, ny) && !visited[ny][nx] && !inFrontier[ny][nx]) {
            frontier.push_back({nx, ny});
            inFrontier[ny][nx] = true;
        }
    }
}

void Maze::generate() {
}

bool Maze::isPassable(int x, int y) const {
    if (x < 0 || x >= MAZE_WIDTH || y < 0 || y >= MAZE_HEIGHT) {
        return false;
    }
    return cells_[y][x];
}

std::vector<std::pair<int, int>> Maze::getPassableCells() const {
    std::vector<std::pair<int, int>> result;
    for (int y = 0; y < MAZE_HEIGHT; ++y) {
        for (int x = 0; x < MAZE_WIDTH; ++x) {
            if (cells_[y][x]) {
                result.emplace_back(x, y);
            }
        }
    }
    return result;
}
