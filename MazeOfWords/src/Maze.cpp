#include "../include/Maze.h"
#include "../include/Config.h"

#include <random>
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
    for (auto& row : cells_) {
        std::fill(row.begin(), row.end(), false);
    }

    static std::mt19937 gen(std::random_device{}());

    std::vector<std::vector<bool>> visited(
        MAZE_HEIGHT,
        std::vector<bool>(MAZE_WIDTH, false)
    );
    std::vector<std::vector<bool>> inFrontier(
        MAZE_HEIGHT,
        std::vector<bool>(MAZE_WIDTH, false)
    );

    std::vector<Cell> frontier;

    int startX = 1;
    int startY = 1;

    visited[startY][startX] = true;
    cells_[startY][startX] = true;

    addFrontier(startX, startY, frontier, inFrontier, visited);

    while (!frontier.empty()) {
        std::uniform_int_distribution<> pickFrontier(
            0,
            static_cast<int>(frontier.size()) - 1
        );
        int idx = pickFrontier(gen);

        Cell current = frontier[idx];
        frontier[idx] = frontier.back();
        frontier.pop_back();

        inFrontier[current.y][current.x] = false;

        std::vector<Cell> visitedNeighbours;
        const int dx[4] = {2, -2, 0, 0};
        const int dy[4] = {0, 0, 2, -2};

        for (int i = 0; i < 4; ++i) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];

            if (inBoundsCell(nx, ny) && visited[ny][nx]) {
                visitedNeighbours.push_back({nx, ny});
            }
        }

        if (visitedNeighbours.empty()) {
            continue;
        }

        std::uniform_int_distribution<> pickNeighbour(
            0,
            static_cast<int>(visitedNeighbours.size()) - 1
        );
        Cell neighbour = visitedNeighbours[pickNeighbour(gen)];

        int wallX = (current.x + neighbour.x) / 2;
        int wallY = (current.y + neighbour.y) / 2;

        visited[current.y][current.x] = true;
        cells_[current.y][current.x] = true;
        cells_[wallY][wallX] = true;

        addFrontier(current.x, current.y, frontier, inFrontier, visited);
    }

    cells_[1][1] = true;
    if (MAZE_WIDTH > 2) {
        cells_[1][2] = true;
    }
    if (MAZE_HEIGHT > 2) {
        cells_[2][1] = true;
    }
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
