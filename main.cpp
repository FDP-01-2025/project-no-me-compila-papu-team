#include "src/SuperTriviaGame.h"
#include "src/all_implementations.cpp"
#include <cstdlib>
#include <ctime>

int main() {
    srand(time(0));
    SuperTriviaGame game;
    game.start();
    return 0;
} 