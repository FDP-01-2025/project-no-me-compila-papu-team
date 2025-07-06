#include "Hangman.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

const int MAX_ATTEMPTS = 6;

class HangmanGame {
private:
    string secretWord;
    string guessedWord;
    vector<char> wrongGuesses;

    void clearConsole() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }

    string pickRandomWord() {
        ifstream file("words.txt");
        vector<string> words;
        string word;

        while (getline(file, word)) {
            if (!word.empty())
                words.push_back(word);
        }

        if (words.empty()) return "COMPUTER"; // fallback
        int index = rand() % words.size();
        return words[index];
    }

    void drawState() {
        clearConsole();
        drawHangman();

        cout << "\nWord: ";
        for (char c : guessedWord)
            cout << c << ' ';

        cout << "\nWrong guesses: ";
        for (char c : wrongGuesses)
            cout << c << ' ';

        cout << "\nAttempts left: " << (MAX_ATTEMPTS - wrongGuesses.size()) << "\n";
    }

    void drawHangman() {
        int attemptsLeft = MAX_ATTEMPTS - wrongGuesses.size();
        cout << "\n";
        cout << "  +---+\n";
        cout << "  |   |\n";

        // Head
        cout << (attemptsLeft < 6 ? "  O   |\n" : "      |\n");

        // Body + arms
        if (attemptsLeft < 4) {
            cout << " /|\\  |\n"; // full arms
        } else if (attemptsLeft < 5) {
            cout << " /|   |\n"; // one arm
        } else if (attemptsLeft < 6) {
            cout << "  |   |\n"; // just body
        } else {
            cout << "      |\n";
        }

        // Legs
        if (attemptsLeft < 2) {
            cout << " / \\  |\n"; // both legs
        } else if (attemptsLeft < 3) {
            cout << " /    |\n"; // one leg
        } else {
            cout << "      |\n";
        }

        cout << "      |\n";
        cout << "=========\n";
    }

    bool isGameWon() {
        return guessedWord == secretWord;
    }

    bool isGameOver() {
        return wrongGuesses.size() >= MAX_ATTEMPTS;
    }

    char getPlayerGuess() {
        char guess;
        cout << "\nEnter a letter: ";
        cin >> guess;
        return toupper(guess);
    }

    void updateGame(char guess) {
        bool found = false;
        for (size_t i = 0; i < secretWord.length(); ++i) {
            if (secretWord[i] == guess) {
                guessedWord[i] = guess;
                found = true;
            }
        }
        if (!found && find(wrongGuesses.begin(), wrongGuesses.end(), guess) == wrongGuesses.end()) {
            wrongGuesses.push_back(guess);
        }
    }

public:
    HangmanGame() {
        srand(time(0));
        secretWord = pickRandomWord();
        guessedWord = string(secretWord.length(), '_');
    }

    void run() {
        cout << "Welcome to Hangman!\n";
        while (!isGameWon() && !isGameOver()) {
            drawState();
            char guess = getPlayerGuess();
            updateGame(guess);
        }

        drawState();
        if (isGameWon())
            cout << "\n You won! The word was: " << secretWord << "\n";
        else
            cout << "\n You lost! The word was: " << secretWord << "\n";
    }
};

// Interfaz pública
Hangman::Hangman() {}

bool Hangman::play() {
    HangmanGame game;
    game.run();
    // Return true if player won, false otherwise
    return game.isGameWon();
}