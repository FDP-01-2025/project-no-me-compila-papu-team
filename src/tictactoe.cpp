#include "TicTacToe.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class InternalTicTacToe {
public:
    vector<char> board;
    char playerMark = 'X';
    char computerMark = 'O';

    InternalTicTacToe() {
        board = vector<char>(9, ' ');
        srand(time(0));
    }

    void drawBoard() {
        cout << endl;
        cout << " " << board[0] << " | " << board[1] << " | " << board[2] << endl;
        cout << "---+---+---" << endl;
        cout << " " << board[3] << " | " << board[4] << " | " << board[5] << endl;
        cout << "---+---+---" << endl;
        cout << " " << board[6] << " | " << board[7] << " | " << board[8] << endl << endl;
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
            if (isWinner(computerMark)) {
                cout << "Computer wins!" << endl;
                break;
            }
            if (isFull()) {
                cout << "It's a tie!" << endl;
                break;
            }
        }
    }
};

// ============ INTERFAZ PÚBLICA ============

TicTacToe::TicTacToe() {}

void TicTacToe::play() {
    InternalTicTacToe game;
    game.run();
}