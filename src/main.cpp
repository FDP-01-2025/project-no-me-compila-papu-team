#include <iostream>
#include <limits>
#include "hangman.h"
#include "tictactoe.h"
#include "utils.h"

using namespace std;

// function to show the main menu
void showMainMenu() {
    cout << "\n══════ ¿QUIÉN QUIERE DEJAR DE SER POBRE? ══════\n";
    cout << "💰 1. Hangman Game - Earn Knowledge Points!\n";
    cout << "🎯 2. Tic Tac Toe Game - Strategy Challenge!\n";
    cout << "🏆 3. View High Scores - Hall of Fame!\n";
    cout << "🚪 4. Exit\n";
    cout << "Select your path to wealth: ";
}

// main function - only calls other functions like professor asked
int main() {
    int choice;
    bool running = true;
    
    // show welcome screen first
    displayWelcomeMessage();
    
    // main game loop
    while(running) {
        showMainMenu();
        cin >> choice;
        
        // check for invalid input
        if (cin.fail()) {
            clearInputBuffer();
            cout << "Invalid option. Please try again.\n";
            continue;
        }
        
        // handle menu choices
        switch (choice) {
            case 1: {
                Hangman hangmanGame;
                hangmanGame.startGame();
                break;
            }
            case 2: {
                TicTacToe ticTacToeGame;
                ticTacToeGame.startGame();
                break;
            }
            case 3:
                displayHighScores(); // show scores from file
                break;
            case 4:
                cout << "Thanks for playing! Goodbye!\n";
                running = false;
                break;
            default:
                cout << "Invalid option. Please try again.\n";
                break;
        }
    }
    
    return 0;
} 