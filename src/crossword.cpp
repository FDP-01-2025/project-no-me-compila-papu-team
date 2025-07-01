#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <windows.h>

using namespace std;

const int SIZE = 12;
char board[SIZE][SIZE];
bool highlighted[SIZE][SIZE] = { false };
vector<string> wordList;
vector<string> foundWords;

enum Direction { HORIZONTAL, VERTICAL, DIAGONAL };

void setConsoleColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void initializeBoard() {
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            board[i][j] = 'A' + rand() % 26;
}

bool canPlaceWord(string word, int row, int col, Direction dir) {
    int len = word.length();
    if (dir == HORIZONTAL && col + len > SIZE) return false;
    if (dir == VERTICAL && row + len > SIZE) return false;
    if (dir == DIAGONAL && (row + len > SIZE || col + len > SIZE)) return false;

    for (int i = 0; i < len; i++) {
        int r = row + (dir == VERTICAL || dir == DIAGONAL ? i : 0);
        int c = col + (dir == HORIZONTAL || dir == DIAGONAL ? i : 0);
        if (board[r][c] != ' ' && board[r][c] != word[i])
            return false;
    }

    return true;
}

void placeWord(string word) {
    Direction dir;
    int row, col;
    bool placed = false;
    while (!placed) {
        dir = static_cast<Direction>(rand() % 3);
        row = rand() % SIZE;
        col = rand() % SIZE;
        if (canPlaceWord(word, row, col, dir)) {
            for (int i = 0; i < word.length(); i++) {
                int r = row + (dir == VERTICAL || dir == DIAGONAL ? i : 0);
                int c = col + (dir == HORIZONTAL || dir == DIAGONAL ? i : 0);
                board[r][c] = word[i];
            }
            placed = true;
        }
    }
}

void printBoard() {
    cout << "\n   === COMPUTER SCIENCE WORD SEARCH ===\n\n";
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (highlighted[i][j]) {
                setConsoleColor(10); // green
                cout << board[i][j] << " ";
                setConsoleColor(7);  // white
            } else {
                cout << board[i][j] << " ";
            }
        }
        cout << endl;
    }

    cout << "\nWords to find:\n";
    for (const string& word : wordList) {
        if (find(foundWords.begin(), foundWords.end(), word) == wordList.end()) {
            cout << "- " << word << endl;
        }
    }
}

void highlightWord(string word) {
    int len = word.length();

    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {

            // HORIZONTAL
            if (col + len <= SIZE) {
                bool match = true;
                for (int i = 0; i < len; i++)
                    if (board[row][col + i] != word[i]) match = false;
                if (match)
                    for (int i = 0; i < len; i++)
                        highlighted[row][col + i] = true;
            }

            // VERTICAL
            if (row + len <= SIZE) {
                bool match = true;
                for (int i = 0; i < len; i++)
                    if (board[row + i][col] != word[i]) match = false;
                if (match)
                    for (int i = 0; i < len; i++)
                        highlighted[row + i][col] = true;
            }

            // DIAGONAL
            if (row + len <= SIZE && col + len <= SIZE) {
                bool match = true;
                for (int i = 0; i < len; i++)
                    if (board[row + i][col + i] != word[i]) match = false;
                if (match)
                    for (int i = 0; i < len; i++)
                        highlighted[row + i][col + i] = true;
            }
        }
    }
}

void toUpperCase(string& str) {
    transform(str.begin(), str.end(), str.begin(), ::toupper);
}

bool isAlreadyFound(string word) {
    return find(foundWords.begin(), foundWords.end(), word) != foundWords.end();
}

bool loadWordsFromFile(const string& filename) {
    ifstream file(filename);
    string word;
    if (!file.is_open()) {
        cerr << "Error: Could not open file: " << filename << endl;
        return false;
    }

    while (getline(file, word)) {
        toUpperCase(word);
        if (!word.empty())
            wordList.push_back(word);
    }

    file.close();
    return true;
}

void playGame() {
    string input;

    while (foundWords.size() < wordList.size()) {
        printBoard();
        cout << "\nEnter a word you've found (or type 'exit' to quit): ";
        cin >> input;
        toUpperCase(input);

        if (input == "EXIT" || input == "QUIT") {
            cout << "\nYou chose to exit early.\n";
            break;
        }

        if (find(wordList.begin(), wordList.end(), input) != wordList.end()) {
            if (isAlreadyFound(input)) {
                cout << "You already found that word.\n";
            } else {
                cout << "Correct! Word found: " << input << "\n";
                foundWords.push_back(input);
                highlightWord(input);
            }
        } else {
            cout << "That word is not on the list or is misspelled.\n";
        }
    }

    cout << "\n🏁 Final Score: " << foundWords.size() << " out of " << wordList.size() << " words found.\n";
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    memset(board, ' ', sizeof(board));
    initializeBoard();

    if (!loadWordsFromFile("words.txt")) {
        return 1;
    }

    for (string word : wordList)
        placeWord(word);

    playGame();
    return 0;
}