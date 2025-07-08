#include "RPSGame.h"
#include "SpriteDisplay.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

const string ROCK_LEFT[6] = {
    "    _______       ",
    "---'   ____)      ",
    "      (_____)     ",
    "      (_____)     ",
    "      (____)      ",
    "---.__(___)       "
};

const string PAPER_LEFT[6] = {
    "     _______      ",
    "---'   ____)____  ",
    "          ______) ",
    "          _______)",
    "         _______) ",
    "---.__________)   "
};

const string SCISSORS_LEFT[6] = {
    "     _______      ",
    "---'   ____)____  ",
    "          ______) ",
    "       __________)",
    "      (____)      ",
    "---.__(___)       "
};

const string ROCK_RIGHT[6] = {
    "       _______    ",
    "      (____   '---",
    "     (_____)      ",
    "     (_____)      ",
    "      (____)      ",
    "       (___)__.---"
};

const string PAPER_RIGHT[6] = {
    "      _______     ",
    "  ____(____   '---",
    " (______          ",
    "(_______          ",
    " (_______         ",
    "   (__________.---"
};

const string SCISSORS_RIGHT[6] = {
    "      _______     ",
    "  ____(____   '---",
    " (______          ",
    "(__________       ",
    "      (____)      ",
    "       (___)__.---"
};

const string VS[6] = {
    " __      ____   ",
    " \\ \\    / ___|  ",
    "  \\ \\  | |___   ",
    "   \\ \\  \\___ \\  ",
    "    \\ \\ ___| |  ",
    "     \\_\\____/   "
};

enum Move { ROCK = 0, PAPER = 1, SCISSORS = 2 };

class RPSInternal {
private:
    void clearConsole() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }

    string getMoveName(int move) {
        switch (move) {
            case ROCK: return "Rock";
            case PAPER: return "Paper";
            case SCISSORS: return "Scissors";
            default: return "";
        }
    }

    const string* getLeftArt(int move) {
        switch (move) {
            case ROCK: return ROCK_LEFT;
            case PAPER: return PAPER_LEFT;
            case SCISSORS: return SCISSORS_LEFT;
            default: return ROCK_LEFT;
        }
    }

    const string* getRightArt(int move) {
        switch (move) {
            case ROCK: return ROCK_RIGHT;
            case PAPER: return PAPER_RIGHT;
            case SCISSORS: return SCISSORS_RIGHT;
            default: return ROCK_RIGHT;
        }
    }

    void decideWinner(int playerMove, int computerMove) {
        if (playerMove == computerMove) {
            cout << "\n It's a tie!\n";
        } else if ((playerMove == ROCK && computerMove == SCISSORS) ||
                   (playerMove == PAPER && computerMove == ROCK) ||
                   (playerMove == SCISSORS && computerMove == PAPER)) {
            cout << "\n You win!\n";
        } else {
            cout << "\n Computer wins!\n";
        }
    }

public:
    void drawHands(int playerMove, int computerMove) {
        clearConsole();
        const string* left = getLeftArt(playerMove);
        const string* right = getRightArt(computerMove);
        cout << "\nYou chose: " << getMoveName(playerMove)
             << "    VS    Computer chose: " << getMoveName(computerMove) << "\n\n";
        for (int i = 0; i < 6; ++i) {
            cout << left[i] << "   " << VS[i] << "   " << right[i] << endl;
        }
    }

    void run() {
        srand(time(0));
        cout << " Rock, Paper, Scissors - Best of 1!\n";
        cout << "Choose your move:\n0 - Rock (✊)\n1 - Paper (✋)\n2 - Scissors (✌️)\n";
        int playerMove;
        while (true) {
            cout << "Your choice: ";
            cin >> playerMove;
            if (playerMove >= 0 && playerMove <= 2) break;
            cout << "Invalid input. Try again.\n";
        }

        int computerMove = rand() % 3;

        drawHands(playerMove, computerMove);
        decideWinner(playerMove, computerMove);
    }
};

// ========== Public interface ==========
RPSGame::RPSGame() {}
bool RPSGame::play() {
    RPSInternal game;
    srand(time(0));
    int playerScore = 0, computerScore = 0;
    for (int round = 1; round <= 3; ++round) {
        clearScreen();
        displayRPSRound(round);
        cout << "Choose your move:\n0 - Rock (✊)\n1 - Paper (✋)\n2 - Scissors (✌️)\n";
        int playerMove;
        while (true) {
            cout << "Your choice: ";
            cin >> playerMove;
            if (playerMove >= 0 && playerMove <= 2) break;
            displayRPSMessage("Invalid input. Try again.", "\033[1;31m");
        }
        int computerMove = rand() % 3;
        // Mostrar manos
        const string* left = nullptr;
        const string* right = nullptr;
        switch (playerMove) {
            case 0: left = ROCK_LEFT; break;
            case 1: left = PAPER_LEFT; break;
            case 2: left = SCISSORS_LEFT; break;
        }
        switch (computerMove) {
            case 0: right = ROCK_RIGHT; break;
            case 1: right = PAPER_RIGHT; break;
            case 2: right = SCISSORS_RIGHT; break;
        }
        clearScreen();
        displayRPSHands(left, right, playerMove, computerMove);
        // Determine round winner
        if (playerMove == computerMove) {
            displayRPSMessage("🤝 Tie in this round!", "\033[1;33m");
        } else if ((playerMove == 0 && computerMove == 2) ||
                   (playerMove == 1 && computerMove == 0) ||
                   (playerMove == 2 && computerMove == 1)) {
            displayRPSMessage("🏆 You won this round!", "\033[1;32m");
            playerScore++;
        } else {
            displayRPSMessage("❌ The computer wins this round!", "\033[1;31m");
            computerScore++;
        }
        cout << "Press any key to continue...";
        cin.ignore();
        cin.get();
    }
    // Show overall winner
    if (playerScore > computerScore) {
        displayRPSMessage("🏆 You won the mini-game!", "\033[1;32m");
        return true;
    } else if (computerScore > playerScore) {
        displayRPSMessage("❌ The computer wins the mini-game!", "\033[1;31m");
        return false;
    } else {
        displayRPSMessage("🤝 Tie in the mini-game!", "\033[1;33m");
        return false;
    }
}