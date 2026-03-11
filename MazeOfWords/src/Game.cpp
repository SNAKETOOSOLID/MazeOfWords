#include "Game.h"

Game::Game(const std::vector<std::string>& words)
        : wordManager_(words), targetWord_(wordManager_.getTargetWord()) {
}

int Game::handleKey(int key) {
    return 0;
}

void Game::run(bool& restartFlag, bool& exitFlag) {
}
