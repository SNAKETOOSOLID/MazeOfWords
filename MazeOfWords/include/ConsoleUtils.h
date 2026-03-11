#pragma once

#include <string>
#include <windows.h>

extern HANDLE hConsole;

void setColor(WORD color);
std::string repeatText(const std::string& s, int count);