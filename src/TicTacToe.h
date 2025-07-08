#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <vector>

class TicTacToe {
private:
    std::vector<char> board;
    char playerMark = 'X';
    char computerMark = 'O';
    
    void clearConsole();
    void drawBoard();
    bool isWinner(char mark);
    bool isFull();
    int getPlayerMove();
    int getComputerMove();

public:
    TicTacToe();        // Constructor
    bool play();        // Runs the game, returns true if the player wins
};

#endif
