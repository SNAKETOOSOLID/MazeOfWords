#pragma once

#include <random>
#include <string>

class MultiplicationQuestion {
    int a_;
    int b_;
    int result_;
public:
    MultiplicationQuestion() {
        static std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<> dis(2, 9);
        a_ = dis(gen);
        b_ = dis(gen);
        result_ = a_ * b_;
    }
    std::string prompt() const {
        return std::to_string(a_) + " * " + std::to_string(b_) + " = ?";
    }
    bool check(int answer) const {
        return answer == result_;
    }
};