#include <gtest/gtest.h>
#include "Entity.h"

TEST(PlayerTest, InitialPositionAndSymbol) {
    Player player(2, 3);
    EXPECT_EQ(player.getX(), 2);
    EXPECT_EQ(player.getY(), 3);
    EXPECT_EQ(player.getSymbol(), '@');

    player.setStandingOnObject(true);
    EXPECT_EQ(player.getSymbol(), '.');

    player.setStandingOnObject(false);
    EXPECT_EQ(player.getSymbol(), '@');
}

TEST(PlayerTest, SetPosition) {
    Player player(0, 0);
    player.setPosition(5, 7);
    EXPECT_EQ(player.getX(), 5);
    EXPECT_EQ(player.getY(), 7);
}

TEST(HintTest, InitialState) {
    Hint hint(10, 20);
    EXPECT_EQ(hint.getX(), 10);
    EXPECT_EQ(hint.getY(), 20);
    EXPECT_EQ(hint.getSymbol(), '?');
    EXPECT_FALSE(hint.isCollected());

    hint.collect();
    EXPECT_TRUE(hint.isCollected());
    EXPECT_EQ(hint.getSymbol(), ' ');
}

TEST(HintTest, QuestionMethods) {
    Hint hint(1, 1);
}

TEST(FinalDoorTest, InitialState) {
    FinalDoor door(3, 4);
    EXPECT_EQ(door.getX(), 3);
    EXPECT_EQ(door.getY(), 4);
    EXPECT_EQ(door.getSymbol(), 'X');
    EXPECT_FALSE(door.isOpened());

    door.open('/');
    EXPECT_TRUE(door.isOpened());
    EXPECT_EQ(door.getSymbol(), '/');
}

TEST(FinalDoorTest, OpenWithDifferentSymbols) {
    FinalDoor door(0, 0);
    door.open('\\');
    EXPECT_EQ(door.getSymbol(), '\\');
}