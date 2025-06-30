#include "tictactoe.h"
#include "utils.h"
#include <iostream>
#include <limits>

using namespace std;

// constructor for tic tac toe game
TicTacToe::TicTacToe() : playerSymbol('X'), computerSymbol('O'), gameRunning(true), score(0) {
    createDefaultFiles();
    initializeBoard();
}

// sets up empty board
void TicTacToe::initializeBoard() {
    for (int i = 0; i < 9; i++) {
        board[i] = ' '; // fill with spaces
    }
}

void TicTacToe::resetGame() {
    initializeBoard();
    gameRunning = true;
    score = 0;
}

void TicTacToe::drawBoard() {
    cout << "\n";
    cout << "     |     |     " << "\n";
    cout << "  " << board[0] << "  |  " << board[1] << "  |  " << board[2] << "  " << "\n";
    cout << "_____|_____|_____" << "\n";
    cout << "     |     |     " << "\n";
    cout << "  " << board[3] << "  |  " << board[4] << "  |  " << board[5] << "  " << "\n";
    cout << "_____|_____|_____" << "\n";
    cout << "     |     |     " << "\n";
    cout << "  " << board[6] << "  |  " << board[7] << "  |  " << board[8] << "  " << "\n";
    cout << "     |     |     " << "\n";
    cout << "\n";
}

void TicTacToe::displayGameRules() {
    cout << "\n=== TIC TAC TOE RULES ===\n";
    cout << "1. You are X, Computer is O\n";
    cout << "2. Enter numbers 1-9 to place your symbol\n";
    cout << "3. Board positions:\n";
    cout << "   1 | 2 | 3\n";
    cout << "   4 | 5 | 6\n";
    cout << "   7 | 8 | 9\n";
    cout << "4. Get three in a row to win!\n\n";
}

bool TicTacToe::isValidMove(int position) {
    return (position >= 0 && position < 9 && board[position] == ' ');
}

// handles player's turn
void TicTacToe::playerTurn() {
    int position;
    bool validMove = false;
    
    // keep asking until they enter valid move
    while(!validMove) {
        cout << "Enter a number (1-9) to place your " << playerSymbol << ": ";
        cin >> position;
        
        // check for invalid input
        if (cin.fail()) {
            clearInputBuffer();
            cout << "Invalid input. Please enter a number between 1 and 9.\n";
            continue;
        }
        
        position--; // convert to array index (0-8)
        
        // check if move is valid
        if (isValidMove(position)) {
            board[position] = playerSymbol;
            validMove = true;
        } else {
            cout << "Invalid move. That position is already taken or out of range.\n";
        }
    }
}

// finds a winning move for given symbol
int TicTacToe::findWinningMove(char symbol) {
    // all possible ways to win
    int winningCombinations[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // columns
        {0, 4, 8}, {2, 4, 6}             // diagonals
    };
    
    // check each winning combination
    for (int i = 0; i < 8; i++) {
        int count = 0;
        int emptyPos = -1;
        
        // count symbols in this combination
        for (int j = 0; j < 3; j++) {
            if (board[winningCombinations[i][j]] == symbol) {
                count++;
            } else if (board[winningCombinations[i][j]] == ' ') {
                emptyPos = winningCombinations[i][j];
            }
        }
        
        // if 2 symbols and 1 empty spot, we can win!
        if (count == 2 && emptyPos != -1) {
            return emptyPos;
        }
    }
    
    return -1; // no winning move found
}

int TicTacToe::findBlockingMove() {
    return findWinningMove(playerSymbol);
}

int TicTacToe::findBestMove() {
    // Priority 1: Win if possible
    int winMove = findWinningMove(computerSymbol);
    if (winMove != -1) {
        return winMove;
    }
    
    // Priority 2: Block player from winning
    int blockMove = findBlockingMove();
    if (blockMove != -1) {
        return blockMove;
    }
    
    // Priority 3: Take center if available
    if (board[4] == ' ') {
        return 4;
    }
    
    // Priority 4: Take corners
    int corners[] = {0, 2, 6, 8};
    for (int i = 0; i < 4; i++) {
        if (board[corners[i]] == ' ') {
            return corners[i];
        }
    }
    
    // Priority 5: Take any available spot
    for (int i = 0; i < 9; i++) {
        if (board[i] == ' ') {
            return i;
        }
    }
    
    return -1;
}

// computer makes its move
void TicTacToe::computerTurn() {
    int position = findBestMove();
    
    if(position != -1) {
        board[position] = computerSymbol;
        cout << "Computer chose position " << (position + 1) << "\n";
    }
}

bool TicTacToe::checkWinner() {
    // Check horizontal, vertical, and diagonal combinations
    int winningCombinations[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Horizontal
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Vertical
        {0, 4, 8}, {2, 4, 6}             // Diagonal
    };
    
    for (int i = 0; i < 8; i++) {
        if (board[winningCombinations[i][0]] != ' ' &&
            board[winningCombinations[i][0]] == board[winningCombinations[i][1]] &&
            board[winningCombinations[i][1]] == board[winningCombinations[i][2]]) {
            return true;
        }
    }
    
    return false;
}

bool TicTacToe::checkTie() {
    for (int i = 0; i < 9; i++) {
        if (board[i] == ' ') {
            return false;
        }
    }
    return true;
}

char TicTacToe::getWinner() {
    int winningCombinations[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Horizontal
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Vertical
        {0, 4, 8}, {2, 4, 6}             // Diagonal
    };
    
    for (int i = 0; i < 8; i++) {
        if (board[winningCombinations[i][0]] != ' ' &&
            board[winningCombinations[i][0]] == board[winningCombinations[i][1]] &&
            board[winningCombinations[i][1]] == board[winningCombinations[i][2]]) {
            return board[winningCombinations[i][0]];
        }
    }
    
    return ' ';
}

void TicTacToe::calculateScore() {
    char winner = getWinner();
    if (winner == playerSymbol) {
        score = 100; // Player wins
    } else if (winner == computerSymbol) {
        score = 0;   // Computer wins
    } else {
        score = 50;  // Tie
    }
}

void TicTacToe::getPlayerName() {
    cout << "\nEnter your name for the high score: ";
    cin.ignore();
    getline(cin, playerName);
    if (playerName.empty()) {
        playerName = "Anonymous";
    }
}

void TicTacToe::saveScore() {
    getPlayerName();
    saveScoreToFile(playerName, score, "TicTacToe");
}

void TicTacToe::announceResult() {
    char winner = getWinner();
    
    if (winner == playerSymbol) {
        cout << "\n*** CONGRATULATIONS! YOU WON! ***\n";
        cout << "You beat the computer!\n";
    } else if (winner == computerSymbol) {
        cout << "\n*** COMPUTER WINS! ***\n";
        cout << "Better luck next time!\n";
    } else {
        cout << "\n*** IT'S A TIE! ***\n";
        cout << "Good game!\n";
    }
    
    calculateScore();
    cout << "Your score: " << score << " points\n";
    saveScore();
}

void TicTacToe::playGame() {
    cout << "\n=== TIC TAC TOE GAME ===\n";
    displayGameRules();
    drawBoard();
    
    while (gameRunning) {
        // Player's turn
        playerTurn();
        drawBoard();
        
        if (checkWinner()) {
            announceResult();
            gameRunning = false;
            break;
        }
        
        if (checkTie()) {
            announceResult();
            gameRunning = false;
            break;
        }
        
        // Computer's turn
        computerTurn();
        drawBoard();
        
        if (checkWinner()) {
            announceResult();
            gameRunning = false;
            break;
        }
        
        if (checkTie()) {
            announceResult();
            gameRunning = false;
            break;
        }
    }
}

void TicTacToe::showGameMenu() {
    while (true) {
        cout << "\n=== TIC TAC TOE MENU ===\n";
        cout << "1. Play Game\n";
        cout << "2. Back to Main Menu\n";
        cout << "Select an option: ";
        
        int option;
        cin >> option;
        
        if (cin.fail()) {
            clearInputBuffer();
            cout << "Invalid option. Try again.\n";
            continue;
        }
        
        switch (option) {
            case 1:
                resetGame();
                playGame();
                break;
            case 2:
                return;
            default:
                cout << "Invalid option. Try again.\n";
                break;
        }
    }
}

void TicTacToe::startGame() {
    showGameMenu();
} 