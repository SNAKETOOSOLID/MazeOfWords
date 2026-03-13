#pragma once
#include <optional>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

struct WordEntry {
    std::string word;
    std::string definition;
};
class WordManager {
    std::vector<WordEntry> entries_;
    WordEntry currentEntry_;
    std::mt19937 gen_;
public:
    explicit WordManager(const std::vector<WordEntry>& entries)
    : entries_(entries), gen_(std::random_device{}()) {
        if (entries_.empty()) {
            throw std::runtime_error("Word list is empty");
        }
        chooseRandomWord();
    }
    void chooseRandomWord() {
        std::uniform_int_distribution<> dist(0,
        static_cast<int>(entries_.size()) - 1);
        currentEntry_ = entries_[dist(gen_)];
    }
    const std::string& getTargetWord() const {
        return currentEntry_.word;
    }
    const std::string& getTargetDefinition() const {
        return currentEntry_.definition;
    }
    std::optional<size_t> getRandomHiddenIndex(const std::vector<bool>& revealed) {
        std::vector<size_t> hidden;
        for (size_t i = 0; i < currentEntry_.word.size(); ++i) {
            if (!revealed[i]) {
                hidden.push_back(i);
            }
        }
        if (hidden.empty()) {
            return std::nullopt;
        }
        std::uniform_int_distribution<> dist(0, static_cast<int>(hidden.size()) - 1);
        return hidden[dist(gen_)];
    }
};