#include <gtest/gtest.h>
#include "WordManager.h"

TEST(WordManagerTest, ConstructorThrowsOnEmptyList) {
    std::vector<WordEntry> empty;
    EXPECT_THROW(WordManager wm(empty), std::runtime_error);
}

TEST(WordManagerTest, ConstructorSelectsWord) {
    std::vector<WordEntry> entries = {
            {"HELLO", "A greeting"},
            {"WORLD", "The earth"},
            {"TEST",  "An examination"}
    };
    WordManager wm(entries);
    std::string word = wm.getTargetWord();
    std::string def = wm.getTargetDefinition();

    bool found = false;
    for (const auto& e : entries) {
        if (e.word == word && e.definition == def) {
            found = true;
            break;
        }
    }
    EXPECT_TRUE(found);
}

TEST(WordManagerTest, GetRandomHiddenIndex) {
    std::vector<WordEntry> entries = {{"ABCDE", "Test word"}};
    WordManager wm(entries);
    std::vector<bool> revealed(5, false);

    auto opt = wm.getRandomHiddenIndex(revealed);
    ASSERT_TRUE(opt.has_value());
    EXPECT_GE(opt.value(), 0);
    EXPECT_LT(opt.value(), 5);

    revealed[1] = true;
    revealed[3] = true;
    opt = wm.getRandomHiddenIndex(revealed);
    if (opt.has_value()) {
        EXPECT_NE(opt.value(), 1);
        EXPECT_NE(opt.value(), 3);
    }

    std::fill(revealed.begin(), revealed.end(), true);
    opt = wm.getRandomHiddenIndex(revealed);
    EXPECT_FALSE(opt.has_value());
}