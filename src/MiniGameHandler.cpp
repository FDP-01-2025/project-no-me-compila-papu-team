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
    return game.play(); // Now returns true only if player wins
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
    int choice = rand() % 3;

    cout << "\n🎮 MINI-GAME CHALLENGE! 🎮\n";
    cout << "Win this mini-game to earn a Power-Up!\n";
    cout << "Press any key to start...";
    cin.ignore();
    cin.get();

    switch (choice) {
        case 0:
            cout << "\n🎯 TIC TAC TOE CHALLENGE 🎯\n";
            cout << "Play against the computer. Get 3 in a row to win!\n";
            cout << "Press any key to begin...";
            cin.get();
            return playTicTacToe();
        case 1:
            cout << "\n🎭 HANGMAN CHALLENGE 🎭\n";
            cout << "Guess the word before the hangman is complete!\n";
            cout << "Press any key to begin...";
            cin.get();
            return playHangman();
        case 2:
            cout << "\n✂️ ROCK PAPER SCISSORS CHALLENGE ✂️\n";
            cout << "Beat the computer in this classic game!\n";
            cout << "Press any key to begin...";
            cin.get();
            return playRockPaperScissors();
        default:
            return false;
    }
}