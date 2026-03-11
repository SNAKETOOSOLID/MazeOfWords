#include "../include/Maze.h"

Maze::Maze() : cells_(15, std::vector<bool>(15, true)) {}

void Maze::generate() {}

bool Maze::isPassable(int x, int y) const {
    return true;
}

std::vector<std::pair<int, int>> Maze::getPassableCells() const {
    return {};
}