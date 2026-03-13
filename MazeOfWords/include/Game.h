#pragma once

#include "Entity.h"
#include "Maze.h"
#include "WordManager.h"

#include <optional>
#include <string>
#include <vector>
#include <memory>

struct ActiveWordInfo {
    std::string word;
    std::string definition;
};

class Game {
    Maze maze_;
    Player player_{1, 1};
    std::vector<std::unique_ptr<Hint>> hints_;
    std::unique_ptr<FinalDoor> finalDoor_;
    WordManager wordManager_;
    std::unique_ptr<ActiveWordInfo> activeWord_;
    std::string targetWord_;
    std::string targetDefinition_;
    std::vector<bool> revealedLetters_;
    bool gameOver_ = false;
    bool win_ = false;
    std::string statusMessage_;
    int stepCounter_ = 0;
    int scoreMultiplier_ = 1;

    void printFrameHeader() const;
    void drawMazeOnly() const;
    void drawFull() const;
    void showVictoryScreen(bool& restartFlag, bool& exitFlag);

    void processHint(size_t hintIndex);
    void processFinalDoor();
    int handleSingleStep(char dir);

    std::optional<size_t> findHintIndexAt(int x, int y) const;
    bool isFinalDoorAt(int x, int y) const;

    int countRevealedLetters() const;
    int getScoreMultiplier(int revealed) const;
    bool isWordFullyRevealed() const;
    void tryAutoOpenDoor();
    char getOpenedDoorSymbol() const;

    static void clearPendingNewlines();
    static std::string readLineTrimmedSafe();
    static std::optional<int> readOptionalIntLine();

public:
    explicit Game(const std::vector<WordEntry>& entries);
    int handleKey(int key);
    void run(bool& restartFlag, bool& exitFlag);
};