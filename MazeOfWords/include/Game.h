#pragma once

#include "Maze.h"
#include "WordManager.h"
#include "Entity.h"

#include <vector>
#include <string>

class Game {
    Maze maze_;
    Player player_{1, 1};
    WordManager wordManager_;

public:
    explicit Game(const std::vector<std::string>& words);
    void run();
};