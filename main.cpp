#include <cstdlib>
#include <ctime>
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#undef byte
#endif
#include "src/SuperTriviaGame.h"
#include "src/all_implementations.cpp"

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    srand(time(0));
    SuperTriviaGame game;
    game.start();
    return 0;
} 