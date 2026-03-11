#include "../include/Game.h"

#include "../include/Config.h"
#include "../include/ConsoleUtils.h"

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
        throw std::runtime_error("Not enough passable cells for hints and final door");
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

void Game::run(bool& restartFlag, bool& exitFlag) {
}

int Game::handleKey(int key) {
    return 0;
}
