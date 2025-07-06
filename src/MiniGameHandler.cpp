#include "MiniGameHandler.h"
#include "TicTacToe.h"
#include "Hangman.h"
#include "Crossword.h"
#include "RPSGame.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

// Function implementations for the mini-games
bool playTicTacToe() {
    TicTacToe game;
    game.play();
    // For simplicity, assume player wins if they complete the game
    return true;
}

bool playHangman() {
    Hangman game;
    game.play();
    // For simplicity, assume player wins if they complete the game
    return true;
}

bool playCrossword() {
    Crossword game;
    game.play();
    // For simplicity, assume player wins if they complete the game
    return true;
}

bool playRockPaperScissors() {
    RPSGame game;
    game.play();
    // For simplicity, assume player wins if they complete the game
    return true;
}

MiniGameHandler::MiniGameHandler() {}

bool MiniGameHandler::playRandomMiniGame() {
    srand(time(0));
    int choice = rand() % 4;

    cout << "\n Starting a mini-game challenge!\n";

    switch (choice) {
        case 0:
            cout << "\n Tic Tac Toe:\n";
            return playTicTacToe();
        case 1:
            cout << "\n Hangman:\n";
            return playHangman();
        case 2:
            cout << "\n Crossword:\n";
            return playCrossword();
        case 3:
            cout << "\n Rock, Paper, Scissors:\n";
            return playRockPaperScissors();
        default:
            return false;
    }
}