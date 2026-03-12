#include "../include/Game.h"
#include <vector>

int main() {
    std::vector<WordEntry> entries = {
        {"PROGRAM", "A set of instructions for a computer."},
        {"COMPILE", "Convert source code into machine code."},
        {"POINTER", "Variable that stores a memory address."},
        {"LIBRARY", "Collection of pre-written code."},
        {"PRIVATE", "Access modifier restricting visibility."},
        {"VIRTUAL", "Method that can be overridden in a derived class."},
        {"INHERIT", "Mechanism to create a new class from an existing one."},
        {"INTEGER", "Whole number data type."},
        {"BOOLEAN", "Logical data type (true/false)."},
        {"PACKAGE", "Group of related classes or modules."},
        {"VERSION", "Number identifying a software release."},
        {"RELEASE", "Official distribution of a version."},
        {"PROJECT", "Collection of files and settings for a build."},
        {"CONTEXT", "Environment or state of execution."},
        {"COMMAND", "Instruction to be executed."},
        {"DYNAMIC", "Runtime behavior or memory allocation."},
        {"GENERIC", "Type parameterization in programming."},
        {"MUTABLE", "Modifiable variable or object."},
        {"TYPEDEF", "Create a type alias in C/C++."},
        {"CASTING", "Converting between data types."},
        {"DECIMAL", "Base-10 number system."},
        {"BITWISE", "Operations performed on bits."},
        {"EXTENDS", "Keyword for inheritance in Java."},
        {"FINALLY", "Block that always executes after try-catch."},
        {"CONSOLE", "Text-based interface for input/output."},
        {"DISPLAY", "Output device or screen."},
        {"MONITOR", "Screen or synchronization object."},
        {"PRINTER", "Output device for paper."},
        {"SCANNER", "Input device for digitizing."},
        {"NETWORK", "Interconnected computers or devices."}
    };

    bool restartFlag = false;
    bool exitFlag = false;

    Game game(entries);
    game.run(restartFlag, exitFlag);

    return 0;
}