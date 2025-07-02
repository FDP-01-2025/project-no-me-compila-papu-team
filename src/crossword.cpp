#include "crossword.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <cstring>

using namespace std;

const int SIZE = 12;

class CrosswordImpl {
public:
    char board[SIZE][SIZE];
    bool highlighted[SIZE][SIZE] = { false };
    vector<string> wordList;
    vector<string> foundWords;

    enum Direction { HORIZONTAL, VERTICAL, DIAGONAL };

    void setConsoleColor(int color) {
        switch(color) {
            case 10: cout << "\033[32m"; break; // verde
            case 7: cout << "\033[37m"; break; // blanco
            case 12: cout << "\033[31m"; break; // rojo
            case 14: cout << "\033[33m"; break; // amarillo
            case 11: cout << "\033[36m"; break; // cyan
            default: cout << "\033[0m"; break;
        }
    }

    void printInstructions() {
        setConsoleColor(11);
        cout << "\nBienvenido al Crucigrama de Programación.\n";
        setConsoleColor(7);
        cout << "- Escribe las palabras que encuentres en el tablero.\n";
        cout << "- Escribe 'exit' para salir del juego en cualquier momento.\n";
        cout << "- Las palabras deben coincidir exactamente (sin tildes, en mayúsculas).\n";
        cout << "\n¡Buena suerte!\n";
        setConsoleColor(7);
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
        int attempts = 0;
        const int MAX_ATTEMPTS = 1000; // Prevent infinite loop
        
        while (!placed && attempts < MAX_ATTEMPTS) {
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
            attempts++;
        }
        
        if (!placed) {
            cout << "Warning: Could not place word '" << word << "' after " << MAX_ATTEMPTS << " attempts." << endl;
        }
    }

    void printBoard() {
        cout << "\n   === COMPUTER SCIENCE WORD SEARCH ===\n\n";
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (highlighted[i][j]) {
                    setConsoleColor(10); // verde
                    cout << board[i][j] << " ";
                    setConsoleColor(7);  // blanco
                } else {
                    cout << board[i][j] << " ";
                }
            }
            cout << endl;
        }
        setConsoleColor(14);
        cout << "\nPalabras por encontrar: " << (wordList.size() - foundWords.size()) << "/" << wordList.size() << "\n";
        setConsoleColor(7);
        cout << "Palabras a buscar:\n";
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

    void pause() {
        setConsoleColor(14);
        cout << "\nPresiona Enter para continuar...";
        setConsoleColor(7);
        cin.ignore();
        cin.get();
    }

    void showFinalSummary() {
        setConsoleColor(11);
        cout << "\n🏁 Resumen final del crucigrama:\n";
        setConsoleColor(10);
        cout << "Palabras encontradas (" << foundWords.size() << "/" << wordList.size() << "):\n";
        for (const string& word : foundWords) {
            cout << "- " << word << endl;
        }
        setConsoleColor(12);
        cout << "\nPalabras que faltaron:\n";
        for (const string& word : wordList) {
            if (find(foundWords.begin(), foundWords.end(), word) == foundWords.end()) {
                cout << "- " << word << endl;
            }
        }
        setConsoleColor(7);
    }

    void playGame() {
        string input;
        printInstructions();
        while (foundWords.size() < wordList.size()) {
            printBoard();
            cout << "\nIngresa una palabra encontrada (o escribe 'exit' para salir): ";
            cin >> input;
            toUpperCase(input);
            if (input == "EXIT" || input == "QUIT") {
                setConsoleColor(14);
                cout << "\nHas decidido salir del crucigrama antes de terminar.\n";
                setConsoleColor(7);
                break;
            }
            if (find(wordList.begin(), wordList.end(), input) != wordList.end()) {
                if (isAlreadyFound(input)) {
                    setConsoleColor(14);
                    cout << "Ya encontraste esa palabra, prueba con otra.\n";
                    setConsoleColor(7);
                } else {
                    setConsoleColor(10);
                    cout << "¡Correcto! Palabra encontrada: " << input << "\n";
                    setConsoleColor(7);
                    foundWords.push_back(input);
                    highlightWord(input);
                }
            } else {
                setConsoleColor(12);
                cout << "Palabra no válida o no está en la lista.\n";
                setConsoleColor(7);
            }
            cin.ignore();
            pause();
        }
        showFinalSummary();
    }
};

Crossword::Crossword() {}

void Crossword::startGame() {
    cout << "DEBUG: Crossword::startGame() called" << endl;
    srand(static_cast<unsigned int>(time(0)));
    cout << "DEBUG: Random seed initialized" << endl;
    
    CrosswordImpl impl;
    cout << "DEBUG: CrosswordImpl created" << endl;
    
    memset(impl.board, ' ', sizeof(impl.board));
    cout << "DEBUG: Board initialized" << endl;
    
    impl.initializeBoard();
    cout << "DEBUG: Board populated with random letters" << endl;
    
    cout << "DEBUG: Attempting to load words from src/game_data/words.txt" << endl;
    if (!impl.loadWordsFromFile("src/game_data/words.txt")) {
        cout << "ERROR: No se pudo cargar el archivo de palabras." << endl;
        return;
    }
    cout << "DEBUG: Words loaded successfully. Count: " << impl.wordList.size() << endl;
    
    cout << "DEBUG: Placing words on board..." << endl;
    // Use only first 10 words to avoid conflicts
    int wordsToPlace = min(10, (int)impl.wordList.size());
    for (int i = 0; i < wordsToPlace; i++) {
        cout << "DEBUG: Placing word " << (i+1) << "/" << wordsToPlace << ": " << impl.wordList[i] << endl;
        impl.placeWord(impl.wordList[i]);
    }
    cout << "DEBUG: All words placed on board" << endl;
    
    cout << "DEBUG: Starting game loop..." << endl;
    impl.playGame();
    cout << "DEBUG: Game finished" << endl;
}