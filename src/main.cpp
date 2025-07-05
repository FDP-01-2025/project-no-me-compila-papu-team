#include <iostream>
#include <limits>
#include "hangman.h"
#include "tictactoe.h"
#include "rpgfight.h"
#include "rock_paper_scissors.h"
#include "crossword.h"
#include "utils.h"

using namespace std;

// function to show the main menu
void showMainMenu() {
    cout << "\n══════ ¿QUIÉN QUIERE DEJAR DE SER POBRE? ══════\n";
    cout << "💰 1. Hangman Game - Earn Knowledge Points!\n";
    cout << "🎯 2. Tic Tac Toe Game - Strategy Challenge!\n";
    cout << "🧩 3. Crossword - Word Search Challenge!\n";
    cout << "⚔️  4. RPG Fight - Epic Battle Adventure!\n";
    cout << "✂️  5. Rock Paper Scissors - Classic Duel!\n";
    cout << "🏆 6. View High Scores - Hall of Fame!\n";
    cout << "🚪 7. Exit\n";
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
            case 3: {
                Crossword crosswordGame;
                crosswordGame.startGame();
                break;
            }
            case 4: {
                RpgFight rpgGame;
                rpgGame.startGame();
                break;
            }
            case 5: {
                RockPaperScissors rpsGame;
                rpsGame.startGame();
                break;
            }
            case 6:
                displayHighScores(); // show scores from file
                break;
            case 7:
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