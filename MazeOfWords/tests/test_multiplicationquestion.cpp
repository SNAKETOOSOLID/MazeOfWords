#include <gtest/gtest.h>
#include "MultiplicationQuestion.h"

TEST(MultiplicationQuestionTest, ConstructorCreatesValidQuestion) {
    MultiplicationQuestion q;
    std::string prompt = q.prompt();

    size_t starPos = prompt.find(" * ");
    ASSERT_NE(starPos, std::string::npos);
    size_t questionPos = prompt.find(" = ?");
    ASSERT_NE(questionPos, std::string::npos);

    int a = std::stoi(prompt.substr(0, starPos));
    int b = std::stoi(prompt.substr(starPos + 3, questionPos - starPos - 3));

    EXPECT_GE(a, 2);
    EXPECT_LE(a, 9);
    EXPECT_GE(b, 2);
    EXPECT_LE(b, 9);
}

TEST(MultiplicationQuestionTest, CheckCorrectAnswer) {
    MultiplicationQuestion q;
    std::string prompt = q.prompt();

    size_t starPos = prompt.find(" * ");
    size_t questionPos = prompt.find(" = ?");
    int a = std::stoi(prompt.substr(0, starPos));
    int b = std::stoi(prompt.substr(starPos + 3, questionPos - starPos - 3));
    int correct = a * b;

    EXPECT_TRUE(q.check(correct));
    EXPECT_FALSE(q.check(correct + 1));
    EXPECT_FALSE(q.check(correct - 1));
}