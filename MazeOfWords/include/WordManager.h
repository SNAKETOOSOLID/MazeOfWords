#pragma once

#include <optional>
#include <string>
#include <vector>

struct WordEntry {
    std::string word;
    std::string definition;
};

class WordManager {
    std::vector<WordEntry> entries_;
    WordEntry currentEntry_;

public:
    explicit WordManager(const std::vector<WordEntry>& entries);

    void chooseRandomWord();
    const std::string& getTargetWord() const;
    const std::string& getTargetDefinition() const;
    std::optional<size_t> getRandomHiddenIndex(const std::vector<bool>& revealed);
};
