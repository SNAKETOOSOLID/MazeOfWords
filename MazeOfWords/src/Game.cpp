#include "../include/Game.h"
#include "../include/Config.h"
#include "../include/ConsoleUtils.h"

#include <iostream>
#include <algorithm>
#include <random>
#include <stdexcept>
#include <cctype>

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
        hints_.push_back(std::make_unique<Hint>(x, y));
    }

    auto [doorX, doorY] = passable[NUM_HINTS];
    finalDoor_ = std::make_unique<FinalDoor>(doorX, doorY);

    revealedLetters_.assign(targetWord_.size(), false);
    statusMessage_ = "Collect hints, reveal letters and open the door at X.";
}

char Game::getOpenedDoorSymbol() const {
    if (!finalDoor_) {
        return '/';
    }
    
    int x = finalDoor_->getX();
    int y = finalDoor_->getY();
    
    bool wallLeft = !maze_.isPassable(x - 1, y);
    bool wallRight = !maze_.isPassable(x + 1, y);
    bool wallUp = !maze_.isPassable(x, y - 1);
    bool wallDown = !maze_.isPassable(x, y + 1);
    
    if (wallRight || wallUp) {
        return '/';
    }
    
    if (wallLeft || wallDown) {
        return '\\';
    }
    
    return '/';
}

void Game::drawMazeOnly() const {
    printFrameHeader();
    setColor(COLOR_WALL);
    std::cout << '|' << repeatText(H_WALL, MAZE_WIDTH) << "|\n";

    for (int y = 0; y < MAZE_HEIGHT; ++y) {
        setColor(COLOR_WALL);
        std::cout << '|';

        for (int x = 0; x < MAZE_WIDTH; ++x) {
            if (x == player_.getX() && y == player_.getY()) {
                setColor(COLOR_PLAYER);
                std::cout << player_.getSymbol();
                continue;
            }
            bool drawn = false;
            if (finalDoor_ && finalDoor_->getX() == x && finalDoor_->getY() == y) {
                setColor(finalDoor_->isOpened() ? COLOR_FINAL_DOOR_OPEN : COLOR_FINAL_DOOR_CLOSED);
                std::cout << finalDoor_->getSymbol();
                drawn = true;
            }
        
            if (!drawn) {
                for (const auto& hint : hints_) {
                    if (!hint->isCollected() && hint->getX() == x && hint->getY() == y) {
                        setColor(COLOR_HINT);
                        std::cout << hint->getSymbol();
                        drawn = true;
                        break;
                    }
                }
            }
        
            if (!drawn) {
                if (maze_.isPassable(x, y)) {
                    setColor(COLOR_PATH);
                    std::cout << ' ';
                } else {
                    setColor(COLOR_WALL);
                    std::cout << H_WALL;
                }
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

void Game::processHint(size_t hintIndex) {
    player_.setStandingOnObject(true);
    drawMazeOnly();
    setColor(COLOR_DEFAULT);
    std::cout << "Question: " << hints_[hintIndex]->getQuestion().prompt() <<
    "\n";
    std::cout << "Enter answer or press Enter to close: ";
    std::optional<int> answer = readOptionalIntLine();
    if (!answer.has_value()) {
        statusMessage_ = "Hint closed. It is still not collected.";
        player_.setStandingOnObject(false);
        drawFull();
        return;
    }
    if (!hints_[hintIndex]->getQuestion().check(*answer)) {
        statusMessage_ = "Wrong answer! Try again.";
        player_.setStandingOnObject(false);
        drawFull();
        return;
    }
    hints_[hintIndex]->collect();
    auto randomIndex = wordManager_.getRandomHiddenIndex(revealedLetters_);
    if (randomIndex.has_value()) {
        revealedLetters_[*randomIndex] = true;
        statusMessage_ = std::string("Correct answer! You got letter: ") +
        targetWord_[*randomIndex];
        tryAutoOpenDoor();
    } else {
        statusMessage_ = "Correct answer! All letters are already revealed.";
    }
    player_.setStandingOnObject(false);
    drawFull();
}

int Game::countRevealedLetters() const {
    int count = 0;
    for (bool r : revealedLetters_) {
        if (r) {
            ++count;
        }
    }
    return count;
}
bool Game::isWordFullyRevealed() const {
    for (bool r : revealedLetters_) {
        if (!r) {
            return false;
        }
    }
    return true;
}

void Game::tryAutoOpenDoor(){
    if (finalDoor_ && !finalDoor_->isOpened() && isWordFullyRevealed()){
        char openedSymbol = getOpenedDoorSymbol();
        finalDoor_->open(openedSymbol);
        statusMessage_ = "All letters collected. Door opened automatically.";
    }
};

void Game::drawFull() const {
    drawMazeOnly();
    setColor(COLOR_DEFAULT);
    std::cout << "Word: ";
    for (size_t i = 0; i < targetWord_.size(); ++i) {
        if (revealedLetters_[i]) {
            setColor(COLOR_LETTER);
            std::cout << targetWord_[i] << ' ';
        } else {
            setColor(COLOR_DEFAULT);
            std::cout << "_ ";
        }
    }
    setColor(COLOR_DEFAULT);
    std::cout << "\n";
    std::cout << "Controls: W/A/S/D move, R restart, Q exit\n";
    std::cout << "Door: ";
    setColor(COLOR_FINAL_DOOR_CLOSED);
    std::cout<<"X = closed";
    setColor(COLOR_FINAL_DOOR_OPEN);
    std::cout<<"/ or \\ = open\n";
    setColor(COLOR_DEFAULT);
    std::cout << "Message: " << statusMessage_ << "\n";
}

std::optional<size_t> Game::findHintIndexAt(int x, int y) const {
    for (size_t i = 0; i < hints_.size(); ++i) {
        if (!hints_[i]->isCollected() && hints_[i]->getX() == x && hints_[i]->getY() == y) {
            return i;
        }
    }
    return std::nullopt;
}

bool Game::isFinalDoorAt(int x, int y) const {
    return finalDoor_ && finalDoor_->getX() == x && finalDoor_->getY() == y;
}

void Game::processFinalDoor() {
    player_.setStandingOnObject(true);
    drawMazeOnly();
    if (finalDoor_ && finalDoor_->isOpened()) {
        statusMessage_ = "The door is already open. Level completed.";
        win_ = true;
        gameOver_ = true;
        player_.setStandingOnObject(false);
        drawFull();
        return;
    }
    setColor(COLOR_DEFAULT);
    std::cout << "Guess the word: ";
    std::string guess = readLineTrimmedSafe();
    std::string upperGuess = guess;
    std::transform(upperGuess.begin(), upperGuess.end(), upperGuess.begin(),
                   [](unsigned char c) { return
                           static_cast<char>(std::toupper(c)); });
    if (upperGuess == targetWord_) {
        int revealed = countRevealedLetters();
        scoreMultiplier_ = getScoreMultiplier(revealed);
        char openedSymbol = getOpenedDoorSymbol();
        finalDoor_->open(openedSymbol);
        statusMessage_ = "Correct! The door is open. You escaped!";
        win_ = true;
        gameOver_ = true;
        player_.setStandingOnObject(false);
        drawFull();
    } else {
        statusMessage_ = "Wrong word. Try again.";
        player_.setStandingOnObject(false);
        drawFull();
    }
}

void Game::run(bool& restartFlag, bool& exitFlag) {
    drawFull();
    while (!gameOver_) {
        int key = _getwch();
        int action = handleKey(key);
        if (action == 1) {
            restartFlag = true;
            break;
        }
        if (action == 2) {
            exitFlag = true;
            break;
        }
    }
    if (gameOver_ && win_ && !restartFlag && !exitFlag) {
        showVictoryScreen(restartFlag, exitFlag);
    }
}

int Game::handleSingleStep(char dir) {
    int newX = player_.getX();
    int newY = player_.getY();
    
    switch (tolower(static_cast<unsigned char>(dir))) {
        case 'd': ++newX; break;
        case 'a': --newX; break;
        case 'w': --newY; break;
        case 's': ++newY; break;
        default: return 1;
    }
    
    if (!maze_.isPassable(newX, newY)) {
        statusMessage_ = "Wall. You cannot move there.";
        return 1;
    }
    
    player_.setPosition(newX, newY);
    stepCounter_++;
    
    if (isFinalDoorAt(newX, newY)) {
        processFinalDoor();
        return 2;
    }
    
    auto hintIndex = findHintIndexAt(newX, newY);
    if (hintIndex.has_value()) {
        processHint(*hintIndex);
        return 2;
    }
    
    player_.setStandingOnObject(false);
    return 0;
}

void Game::clearPendingNewlines() {
    while (std::cin.peek() == '\n' || std::cin.peek() == '\r') {
        std::cin.get();
    }
}
std::string Game::readLineTrimmedSafe() {
    clearPendingNewlines();
    std::string s;
    std::getline(std::cin, s);
    while (!s.empty() && std::isspace(static_cast<unsigned
    char>(s.front()))) {
        s.erase(s.begin());
    }
    while (!s.empty() && std::isspace(static_cast<unsigned char>(s.back())))
    {
        s.pop_back();
    }
    return s;
}
std::optional<int> Game::readOptionalIntLine() {
    clearPendingNewlines();
    std::string s;
    std::getline(std::cin, s);
    if (s.empty()) {
        return std::nullopt;
    }
    while (!s.empty() && std::isspace(static_cast<unsigned char>(s.front()))) {
        s.erase(s.begin());
    }
    while (!s.empty() && std::isspace(static_cast<unsigned char>(s.back())))
    {
        s.pop_back();
    }
    if (s.empty()) {
        return std::nullopt;
    }
    try {
        size_t pos = 0;
        int value = std::stoi(s, &pos);
        if (pos != s.size()) {
            return std::nullopt;
        }
        return value;
    } catch (...) {
        return std::nullopt;
    }
}


int Game::handleKey(int key) {
    if (key == 0 || key == 224) {
        _getwch();
        return 0;
    }
    
    char c = static_cast<char>(tolower(static_cast<unsigned char>(key)));
    
    if (c == 'r') {
        return 1;
    }
    
    if (c == 'q') {
        return 2;
    }
    
    if (c == 'w' || c == 'a' || c == 's' || c == 'd') {
        int result = handleSingleStep(c);
        if (!gameOver_) {
            if (result == 0) {
                drawMazeOnly();
            } else {
                drawFull();
            }
        }
        return 0;
    }
    
    statusMessage_ = "Use only W/A/S/D, R or Q.";
    drawFull();
    return 0;
}

void Game::showVictoryScreen(bool& restartFlag, bool& exitFlag) {
    setColor(COLOR_LETTER);
    std::cout << "\n========================================\n";
    std::cout << "You escaped the maze!\n";
    int baseScore = std::max(0, MAX_SCORE - stepCounter_ * STEP_PENALTY);
    int finalScore = baseScore * scoreMultiplier_;
    std::cout << "Total steps: " << stepCounter_ << "\n";
    std::cout << "Base score: " << baseScore << "\n";
    std::cout << "Multiplier: x" << scoreMultiplier_ << "\n";
    std::cout << "Final score: " << finalScore << "\n";
    std::cout << "Word: " << targetWord_ << " - " << targetDefinition_ << "\n";
    std::cout << "========================================\n";
    setColor(COLOR_DEFAULT);
    while (true) {
        std::cout << "Press R to restart or Q to exit: ";
        int key = _getwch();
        if (key == 0 || key == 224) {
            _getwch();
            continue;
        }
        char c = static_cast<char>(tolower(static_cast<unsigned char>(key)));
        if (c == 'r') {
            restartFlag = true;
            break;
        }
        if (c == 'q') {
            exitFlag = true;
            break;
        }
    }
}

int Game::getScoreMultiplier(int revealed) const {
    switch (revealed) {
        case 0: return 10;
        case 1: return 9;
        case 2: return 8;
        case 3: return 6;
        case 4: return 4;
        case 5: return 2;
        default: return 1;
    }
}