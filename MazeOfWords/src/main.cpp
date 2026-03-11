#include "../include/Game.h"
#include <vector>

int main() {
    std::vector<WordEntry> entries = {
        {"TEST", "test definition"}
    };

    bool restartFlag = false;
    bool exitFlag = false;

    Game game(entries);
    game.run(restartFlag, exitFlag);

    return 0;
}