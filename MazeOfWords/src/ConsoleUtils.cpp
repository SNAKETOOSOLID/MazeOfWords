#include "ConsoleUtils.h"

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void setColor(WORD color) {
    SetConsoleTextAttribute(hConsole, color);
}

std::string repeatText(const std::string& s, int count) {
    std::string result;
    for (int i = 0; i < count; ++i) {
        result += s;
    }
    return result;
}
