#include "../include/WordManager.h"

#include <string>
#include <optional>

WordManager::WordManager(const std::vector<WordEntry>& entries) {}

const std::string& WordManager::getTargetWord() const
{
    static std::string word = "test";
    return word;
}

const std::string& WordManager::getTargetDefinition() const
{
    static std::string definition = "test definition";
    return definition;
}

std::optional<size_t> WordManager::getRandomHiddenIndex(const std::vector<bool>&)
{
    return std::nullopt;
}