#pragma once
#include "MultiplicationQuestion.h"
#include <variant>

class Entity {
protected:
    int x_;
    int y_;
    public:
    Entity(int x, int y) : x_(x), y_(y) {}
    virtual ~Entity() = default;
    int getX() const { return x_; }
    int getY() const { return y_; }
    void setPosition(int x, int y) {
        x_ = x;
        y_ = y;
    }
    virtual char getSymbol() const = 0;
};
class Player : public Entity {
    bool standingOnObject_ = false;
public:
    Player(int startX, int startY) : Entity(startX, startY) {}
    char getSymbol() const override {
        return standingOnObject_ ? '.' : '@';
    }
    void setStandingOnObject(bool value) {
        standingOnObject_ = value;
    }
};
class FinalDoor : public Entity {
    bool opened_ = false;
    char openedSymbol_ = 'X';
public:
    FinalDoor(int x, int y) : Entity(x, y) {}
    char getSymbol() const override {
        return opened_ ? openedSymbol_ : 'X';
    }
    bool isOpened() const {
        return opened_;
    }
    void open(char symbol) {
        opened_ = true;
        openedSymbol_ = symbol;
    }
};
class Hint : public Entity {
    bool collected_ = false;
    std::variant<MultiplicationQuestion> question_;
public:
    Hint(int x, int y) : Entity(x, y), question_(MultiplicationQuestion()) {}
    char getSymbol() const override {
        return collected_ ? ' ' : '?';
    }
    bool isCollected() const {
        return collected_;
    }
    void collect() {
        collected_ = true;
    }
    const std::variant<MultiplicationQuestion> getQuestion() const {
        return question_;
    }
    std::string getPrompt() const {
        return std::visit([](const auto& q) { return q.prompt(); }, question_);
    }
    bool checkAnswer(int answer) const {
        return std::visit([answer](const auto& q) { return q.check(answer); }, question_);
    }
};