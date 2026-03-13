#pragma once

#include <vector>
#include <utility>

class Maze {
    std::vector<std::vector<bool>> cells_;

    struct Cell {
        int x;
        int y;
    };

    bool inBoundsCell(int x, int y) const;

    void addFrontier(int x, int y, std::vector<Cell>& frontier,
                     std::vector<std::vector<bool>>& inFrontier,
                     const std::vector<std::vector<bool>>& visited);

public:
    Maze();
    void generate();
    bool isPassable(int x, int y) const;
    std::vector<std::pair<int, int>> getPassableCells() const;
};
