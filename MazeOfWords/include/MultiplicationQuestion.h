#pragma once

#include <string>

class MultiplicationQuestion {
public:
    MultiplicationQuestion();
    std::string prompt() const;
    bool check(int answer) const;
};