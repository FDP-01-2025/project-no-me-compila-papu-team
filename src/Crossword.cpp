#include "Crossword.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>

using namespace std;

const int BOARD_SIZE = 12;

class CrosswordGame {
private:
    char board[BOARD_SIZE][BOARD_SIZE];
    vector<string> placedWords;
    vector<pair<int, int>> positions;
    vector<char> directions; // 'H' = horizontal, 'V' = vertical

    void clearConsole() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }

    vector<string> loadWords() {
        ifstream file("words.txt");
        vector<string> words;
        string word;
        while (getline(file, word)) {
            if (!word.empty() && word.length() <= BOARD_SIZE)
                words.push_back(word);
        }
        random_device rd;
        mt19937 g(rd());
        shuffle(words.begin(), words.end(), g);
        return words;
    }

    void initBoard() {
        for (int i = 0; i < BOARD_SIZE; ++i)
            for (int j = 0; j < BOARD_SIZE; ++j)
                board[i][j] = '.';
    }

    void placeWord(const string& word, int row, int col, char direction) {
        if (direction == 'H') {
            for (size_t i = 0; i < word.length(); ++i)
                board[row][col + i] = word[i];
        } else {
            for (size_t i = 0; i < word.length(); ++i)
                board[row + i][col] = word[i];
        }
        placedWords.push_back(word);
        positions.push_back({row, col});
        directions.push_back(direction);
    }

    bool canPlaceWord(const string& word, int row, int col, char direction) {
        if (direction == 'H') {
            if (col + word.length() > BOARD_SIZE) return false;
            for (size_t i = 0; i < word.length(); ++i)
                if (board[row][col + i] != '.' && board[row][col + i] != word[i])
                    return false;
        } else {
            if (row + word.length() > BOARD_SIZE) return false;
            for (size_t i = 0; i < word.length(); ++i)
                if (board[row + i][col] != '.' && board[row + i][col] != word[i])
                    return false;
        }
        return true;
    }

    void fillRandomLetters() {
        for (int i = 0; i < BOARD_SIZE; ++i)
            for (int j = 0; j < BOARD_SIZE; ++j)
                if (board[i][j] == '.')
                    board[i][j] = 'A' + rand() % 26;
    }

    void drawBoard() {
        cout << "\n   ";
        for (int j = 0; j < BOARD_SIZE; ++j)
            cout << j << " ";
        cout << "\n  +" << string(BOARD_SIZE * 2, '-') << "+\n";
        for (int i = 0; i < BOARD_SIZE; ++i) {
            cout << i << " |";
            for (int j = 0; j < BOARD_SIZE; ++j)
                cout << board[i][j] << ' ';
            cout << "|\n";
        }
        cout << "  +" << string(BOARD_SIZE * 2, '-') << "+\n";
    }

    void giveClues() {
        cout << "\n🔍 Word Clues:\n";
        for (size_t i = 0; i < placedWords.size(); ++i) {
            cout << i + 1 << ". (" << positions[i].first << ", " << positions[i].second << ") ";
            cout << (directions[i] == 'H' ? "Horizontal" : "Vertical");
            cout << " - " << placedWords[i].length() << " letters\n";
        }
    }

public:
    CrosswordGame() {
        srand(time(0));
        initBoard();
        auto words = loadWords();
        int count = 0;
        for (const auto& word : words) {
            if (count >= 5) break; // coloca 5 palabras
            int row = rand() % BOARD_SIZE;
            int col = rand() % BOARD_SIZE;
            char dir = (rand() % 2 == 0) ? 'H' : 'V';
            if (canPlaceWord(word, row, col, dir)) {
                placeWord(word, row, col, dir);
                count++;
            }
        }
        fillRandomLetters();
    }

    void run() {
        cout << " Welcome to the Crossword Puzzle!\n";
        drawBoard();
        giveClues();

        cout << "\n(Type the words you find. Type 'EXIT' to quit)\n";
        string guess;
        vector<bool> guessed(placedWords.size(), false);
        int correct = 0;

        while (correct < (int)placedWords.size()) {
            cout << "\nYour guess: ";
            cin >> guess;
            transform(guess.begin(), guess.end(), guess.begin(), ::toupper);
            if (guess == "EXIT") break;

            bool found = false;
            for (size_t i = 0; i < placedWords.size(); ++i) {
                if (!guessed[i] && placedWords[i] == guess) {
                    clearConsole();
                    cout << " Correct!\n";
                    drawBoard();
                    giveClues();
                    cout << "\nFound: " << correct + 1 << "/" << placedWords.size() << " words\n";
                    guessed[i] = true;
                    correct++;
                    found = true;
                }
            }
            if (!found) cout << "Incorrect word.\n";
        }

        cout << "\n Game finished! You found " << correct << " words.\n";
    }
};

// Interfaz pública
Crossword::Crossword() {}
void Crossword::play() {
    CrosswordGame game;
    game.run();
}