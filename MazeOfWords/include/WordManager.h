#pragma once

#include <optional>
#include <string>
#include <vector>

class WordManager {
    std::vector<std::string> wordList_;
    std::string targetWord_;

public:
    explicit WordManager(const std::vector<std::string>& words);

    void chooseRandomWord();
    const std::string& getTargetWord() const;
    std::optional<size_t> getRandomHiddenIndex(const std::vector<bool>& revealed);
};