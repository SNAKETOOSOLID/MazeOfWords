#include "../include/Game.h"

#include <vector>
#include <string>

int main() {
    std::vector<std::string> words = {"PROGRAM", "VECTOR"};
    Game game(words);
    game.run();
    return 0;
}