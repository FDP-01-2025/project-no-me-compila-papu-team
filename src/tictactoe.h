#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <string>

class TicTacToe {
private:
    char board[9];
    char playerSymbol;
    char computerSymbol;
    bool gameRunning;
    int score;
    std::string playerName;
    
    // Game logic methods
    void initializeBoard();
    void resetGame();
    
    // Display methods
    void drawBoard();
    void displayGameRules();
    
    // Player input methods
    void playerTurn();
    bool isValidMove(int position);
    
    // Computer AI methods
    void computerTurn();
    int findBestMove();
    int findWinningMove(char symbol);
    int findBlockingMove();
    
    // Game state methods
    bool checkWinner();
    bool checkTie();
    char getWinner();
    void announceResult();
    
    // Score and file management
    void calculateScore();
    void getPlayerName();
    void saveScore();
    
public:
    TicTacToe();
    void startGame();
    void playGame();
    void showGameMenu();
};

#endif 