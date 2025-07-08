#include "Hangman.h"
#include "SpriteDisplay.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <sstream>

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
        ifstream file("data/words.txt");
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

    string getHangmanArt() {
        int attemptsLeft = MAX_ATTEMPTS - wrongGuesses.size();
        stringstream ss;
        ss << "\n";
        ss << "  +---+\n";
        ss << "  |   |\n";
        ss << (attemptsLeft < 6 ? "  O   |\n" : "      |\n");
        if (attemptsLeft < 4) {
            ss << " /|\\  |\n";
        } else if (attemptsLeft < 5) {
            ss << " /|   |\n";
        } else if (attemptsLeft < 6) {
            ss << "  |   |\n";
        } else {
            ss << "      |\n";
        }
        if (attemptsLeft < 2) {
            ss << " / \\  |\n";
        } else if (attemptsLeft < 3) {
            ss << " /    |\n";
        } else {
            ss << "      |\n";
        }
        ss << "      |\n";
        ss << "=========";
        return ss.str();
    }

    bool isGameOver() {
        return wrongGuesses.size() >= MAX_ATTEMPTS;
    }

    char getPlayerGuess() {
        char guess;
        cout << "\nIngresa una letra: ";
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
        displayHangmanMessage("Welcome to Hangman!", "\033[1;36m");
        while (!isGameWon() && !isGameOver()) {
            clearConsole();
            displayHangmanState(getHangmanArt(), guessedWord, wrongGuesses, MAX_ATTEMPTS - wrongGuesses.size());
            char guess = getPlayerGuess();
            updateGame(guess);
        }
        clearConsole();
        displayHangmanState(getHangmanArt(), guessedWord, wrongGuesses, MAX_ATTEMPTS - wrongGuesses.size());
        if (isGameWon())
            displayHangmanMessage("🏆 You won! The word was: " + secretWord, "\033[1;32m");
        else
            displayHangmanMessage("❌ You lost! The word was: " + secretWord, "\033[1;31m");
    }

    bool isGameWon() {
        return guessedWord == secretWord;
    }
};

// Public interface
Hangman::Hangman() {}

bool Hangman::play() {
    HangmanGame game;
    game.run();
    // Return true if player won, false otherwise
    return game.isGameWon();
}