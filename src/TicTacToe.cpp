#include "TicTacToe.h"
#include "SpriteDisplay.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

// ============ INTERFAZ PÚBLICA ============

TicTacToe::TicTacToe() {
    board = vector<char>(9, ' ');
    srand(time(0));
}

void TicTacToe::clearConsole() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void TicTacToe::drawBoard() {
    displayTicTacToeBoard(board);
}

bool TicTacToe::isWinner(char mark) {
    int winCombos[8][3] = {
        {0,1,2}, {3,4,5}, {6,7,8},
        {0,3,6}, {1,4,7}, {2,5,8},
        {0,4,8}, {2,4,6}
    };
    for (auto &combo : winCombos) {
        if (board[combo[0]] == mark &&
            board[combo[1]] == mark &&
            board[combo[2]] == mark) {
            return true;
        }
    }
    return false;
}

bool TicTacToe::isFull() {
    for (char c : board)
        if (c == ' ') return false;
    return true;
}

int TicTacToe::getPlayerMove() {
    int move;
    while (true) {
        cout << "Enter your move (1-9): ";
        if (cin >> move) {
            move--;
            if (move >= 0 && move < 9 && board[move] == ' ')
                return move;
            else
                cout << "Invalid move. Try again.\n";
        } else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and 9.\n";
        }
    }
}

int TicTacToe::getComputerMove() {
    for (int i = 0; i < 9; i++) {
        if (board[i] == ' ') {
            board[i] = computerMark;
            if (isWinner(computerMark)) {
                board[i] = ' ';
                return i;
            }
            board[i] = ' ';
        }
    }
    for (int i = 0; i < 9; i++) {
        if (board[i] == ' ') {
            board[i] = playerMark;
            if (isWinner(playerMark)) {
                board[i] = ' ';
                return i;
            }
            board[i] = ' ';
        }
    }
    if (board[4] == ' ') return 4;
    int corners[] = {0, 2, 6, 8};
    for (int i : corners)
        if (board[i] == ' ') return i;
    int sides[] = {1, 3, 5, 7};
    for (int i : sides)
        if (board[i] == ' ') return i;
    return -1;
}

bool TicTacToe::play() {
    bool playerWon = false;
    
    // Solo mostrar el mensaje de bienvenida al inicio
    displayTicTacToeMessage("Welcome to Tic-Tac-Toe!", "\033[1;36m");
    drawBoard();
    
    while (true) {
        int player = getPlayerMove();
        board[player] = playerMark;
        clearConsole();
        drawBoard();
        
        if (isWinner(playerMark)) {
            displayTicTacToeMessage("🏆 You won!", "\033[1;32m");
            playerWon = true;
            break;
        }
        if (isFull()) {
            displayTicTacToeMessage("🤝 Tie!", "\033[1;33m");
            cout << "Press any key to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            break;
        }

        int comp = getComputerMove();
        board[comp] = computerMark;

        displayTicTacToeMessage("The computer chose position " + to_string(comp + 1), "\033[1;36m");
        drawBoard();
        cout << "Press any key to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();

        clearConsole();
        drawBoard();

        if (isWinner(computerMark)) {
            displayTicTacToeMessage("❌ The computer wins!", "\033[1;31m");
            cout << "Press any key to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            break;
        }
        if (isFull()) {
            displayTicTacToeMessage("🤝 Tie!", "\033[1;33m");
            cout << "Press any key to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            break;
        }
    }
    return playerWon;
}