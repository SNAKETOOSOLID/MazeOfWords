#pragma once

class Entity {
protected:
    int x_;
    int y_;

public:
    Entity(int x, int y);
    virtual ~Entity() = default;

    int getX() const;
    int getY() const;
    void setPosition(int x, int y);

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
public:
    FinalDoor(int x, int y);
    char getSymbol() const override;
};

class Hint : public Entity {
public:
    Hint(int x, int y);
    char getSymbol() const override;
};