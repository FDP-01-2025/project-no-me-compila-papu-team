#include "TicTacToe.h"
#include "SpriteDisplay.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

class InternalTicTacToe {
public:
    vector<char> board;
    char playerMark = 'X';
    char computerMark = 'O';

    void clearConsole() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }

    InternalTicTacToe() {
        board = vector<char>(9, ' ');
        srand(time(0));
    }

    void drawBoard() {
        displayTicTacToeBoard(board);
    }

    bool isWinner(char mark) {
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

    bool isFull() {
        for (char c : board)
            if (c == ' ') return false;
        return true;
    }

    int getPlayerMove() {
        int move;
        while (true) {
            cout << "Enter your move (1-9): ";
            cin >> move;
            move--;
            if (move >= 0 && move < 9 && board[move] == ' ')
                return move;
            cout << "Invalid move. Try again.\n";
        }
    }

    int getComputerMove() {
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

    void run() {
        cout << "Welcome to Tic-Tac-Toe!" << endl;
        drawBoard();
        while (true) {
            int player = getPlayerMove();
            board[player] = playerMark;
            clearConsole();
            drawBoard();
            if (isWinner(playerMark)) {
                cout << "You win!" << endl;
                break;
            }
            if (isFull()) {
                cout << "It's a tie!" << endl;
                break;
            }

            int comp = getComputerMove();
            board[comp] = computerMark;

            cout << "Computer chose position " << (comp + 1) << endl;
            drawBoard();
            cout << "Press any key to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();

            clearConsole();
            drawBoard();

            if (isWinner(computerMark)) {
                cout << "Computer wins!" << endl;
                cout << "Press any key to continue...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                break;
            }
            if (isFull()) {
                cout << "It's a tie!" << endl;
                cout << "Press any key to continue...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                break;
            }
        }
    }
};

// ============ INTERFAZ PÚBLICA ============

TicTacToe::TicTacToe() {}

bool TicTacToe::play() {
    InternalTicTacToe game;
    bool playerWon = false;
    displayTicTacToeMessage("¡Bienvenido a Tic-Tac-Toe!", "\033[1;36m");
    game.drawBoard();
    while (true) {
        int player = game.getPlayerMove();
        game.board[player] = game.playerMark;
        game.clearConsole();
        game.drawBoard();
        if (game.isWinner(game.playerMark)) {
            displayTicTacToeMessage("🏆 ¡Ganaste!", "\033[1;32m");
            playerWon = true;
            break;
        }
        if (game.isFull()) {
            displayTicTacToeMessage("🤝 ¡Empate!", "\033[1;33m");
            cout << "Presiona cualquier tecla para continuar...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            break;
        }

        int comp = game.getComputerMove();
        game.board[comp] = game.computerMark;

        displayTicTacToeMessage("La computadora eligió la posición " + to_string(comp + 1), "\033[1;36m");
        game.drawBoard();
        cout << "Presiona cualquier tecla para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();

        game.clearConsole();
        game.drawBoard();

        if (game.isWinner(game.computerMark)) {
            displayTicTacToeMessage("❌ ¡La computadora gana!", "\033[1;31m");
            cout << "Presiona cualquier tecla para continuar...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            break;
        }
        if (game.isFull()) {
            displayTicTacToeMessage("🤝 ¡Empate!", "\033[1;33m");
            cout << "Presiona cualquier tecla para continuar...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            break;
        }
    }
    return playerWon;
}