#include "RPSGame.h"
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
    void run() {
        srand(time(0));
        cout << " Rock, Paper, Scissors - Best of 1!\n";
        cout << "Choose your move:\n";
        cout << "0 - Rock\n1 - Paper\n2 - Scissors\n";
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

// ========== Interfaz pública ==========
RPSGame::RPSGame() {}
void RPSGame::play() {
    RPSInternal game;
    game.run();
}