#pragma once

#include "Entity.h"
#include "Maze.h"
#include "WordManager.h"

#include <optional>
#include <string>
#include <vector>

class Game {
    Maze maze_;
    Player player_{1, 1};
    std::vector<Hint> hints_;
    std::optional<FinalDoor> finalDoor_;
    WordManager wordManager_;

    std::string targetWord_;
    std::vector<bool> revealedLetters_;
    bool gameOver_ = false;
    bool win_ = false;
    std::string statusMessage_;
    int stepCounter_ = 0;
    int scoreMultiplier_ = 1;

public:
    explicit Game(const std::vector<std::string>& words);
    int handleKey(int key);
    void run(bool& restartFlag, bool& exitFlag);
};
