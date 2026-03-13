#include <gtest/gtest.h>
#include "Game.h"

TEST(GameTest, ConstructorDoesNotThrow) {
    std::vector<WordEntry> entries = {
            {"TEST", "A trial or examination."}
    };
    EXPECT_NO_THROW(Game game(entries));
}
