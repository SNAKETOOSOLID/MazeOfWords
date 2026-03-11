#pragma once

#include <vector>
#include <utility>

class Maze {
    std::vector<std::vector<bool>> cells_;

public:
    Maze();

    void generate();
    bool isPassable(int x, int y) const;
    std::vector<std::pair<int, int>> getPassableCells() const;
};