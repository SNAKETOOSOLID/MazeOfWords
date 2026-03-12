#include "../include/Game.h"
#include "../include/Config.h"
#include "../include/ConsoleUtils.h"

#include <iostream>
#include <algorithm>
#include <random>
#include <stdexcept>

Game::Game(const std::vector<WordEntry>& entries)
        : wordManager_(entries),
          targetWord_(wordManager_.getTargetWord()),
          targetDefinition_(wordManager_.getTargetDefinition()) {
    auto passable = maze_.getPassableCells();

    passable.erase(
            std::remove_if(
                    passable.begin(),
                    passable.end(),
                    [](const std::pair<int, int>& p) {
                        return p.first == 1 && p.second == 1;
                    }),
            passable.end()
    );

    if (static_cast<int>(passable.size()) < NUM_HINTS + 1) {
        revealedLetters_.assign(targetWord_.size(), true);
        statusMessage_ = "Stub mode: maze is not fully generated yet.";
        return;
    }

    std::shuffle(passable.begin(), passable.end(), std::mt19937(std::random_device{}()));

    for (int i = 0; i < NUM_HINTS; ++i) {
        auto [x, y] = passable[i];
        hints_.emplace_back(x, y);
    }

    auto [doorX, doorY] = passable[NUM_HINTS];
    finalDoor_.emplace(doorX, doorY);

    revealedLetters_.assign(targetWord_.size(), false);
    statusMessage_ = "Collect hints, reveal letters and open the door at X.";
}

void Game::drawMazeOnly() const {
    printFrameHeader();
    setColor(COLOR_WALL);
    std::cout << '|' << repeatText(H_WALL, MAZE_WIDTH) << "|\n";

    for (int y = 0; y < MAZE_HEIGHT; ++y) {
        setColor(COLOR_WALL);
        std::cout << '|';

        for (int x = 0; x < MAZE_WIDTH; ++x) {
            if (maze_.isPassable(x, y)) {
                setColor(COLOR_PATH);
                std::cout << ' ';
            } else {
                setColor(COLOR_WALL);
                std::cout << H_WALL;
            }
        }

        setColor(COLOR_WALL);
        std::cout << "|\n";
    }

    setColor(COLOR_WALL);
    std::cout << '|' << repeatText(H_WALL, MAZE_WIDTH) << "|\n";
    setColor(COLOR_DEFAULT);
}

void Game::printFrameHeader() const {
    setColor(COLOR_DEFAULT);
    std::cout << "\n========================================\n";
}


void Game::run(bool& restartFlag, bool& exitFlag) {
    restartFlag = false;
    exitFlag = false;
    drawMazeOnly();
}

int Game::handleKey(int key) {
    return 0;
}
