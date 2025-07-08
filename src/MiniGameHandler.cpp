#include "MiniGameHandler.h"
#include "SpriteDisplay.h"
#include "TicTacToe.h"
#include "Hangman.h"
#include "RPSGame.h"
#include "GuessNumberGame.h"
#include "MemorySequenceGame.h"
#include "QuickReactionGame.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

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

// --- NUEVOS MINIJUEGOS ---

// 1. Adivina el número
bool MiniGameHandler::playGuessNumber() {
    GuessNumberGame game;
    return game.play();
}

// 2. Memoria rápida (secuencia de números)
bool MiniGameHandler::playMemorySequence() {
    MemorySequenceGame game;
    return game.play();
}

// 3. Reacción rápida
bool MiniGameHandler::playQuickReaction() {
    QuickReactionGame game;
    return game.play();
}

MiniGameHandler::MiniGameHandler() {}

bool MiniGameHandler::playRandomMiniGame() {
    // 0: TicTacToe, 1: Hangman, 2: RPS, 3: GuessNumber, 4: Memory, 5: QuickReaction
    int choice = rand() % 6;
    string gameNames[] = {"Tic-Tac-Toe", "Hangman", "Rock-Paper-Scissors", "Guess the Number", "Memory Sequence", "Quick Reaction"};
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
        case 3:
            return playGuessNumber();
        case 4:
            return playMemorySequence();
        case 5:
            return playQuickReaction();
        default:
            return false;
    }
}