#include "MiniGameHandler.h"
#include "SpriteDisplay.h"
#include "TicTacToe.h"
#include "Hangman.h"
#include "RPSGame.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

// Function implementations for the mini-games
bool playTicTacToe() {
    TicTacToe game;
    return game.play(); // Now returns true only if player wins
}

bool playHangman() {
    Hangman game;
    return game.play(); // Now returns true only if player wins
}

bool playRockPaperScissors() {
    RPSGame game;
    return game.play(); // Now returns true only if player wins
}

MiniGameHandler::MiniGameHandler() {}

bool MiniGameHandler::playRandomMiniGame() {
    int choice = rand() % 3;

    string gameNames[] = {"Tic-Tac-Toe", "Hangman", "Rock-Paper-Scissors"};
    clearScreen();
    displayMiniGameIntro(gameNames[choice]);

    cin.ignore();
    cin.get();

    switch (choice) {
        case 0:
            return playTicTacToe();
        case 1:
            return playHangman();
        case 2:
            return playRockPaperScissors();
        default:
            return false;
    }
}