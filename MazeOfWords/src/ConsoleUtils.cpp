#include "ConsoleUtils.h"

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void setColor(WORD color) {
    SetConsoleTextAttribute(hConsole, color);
}

