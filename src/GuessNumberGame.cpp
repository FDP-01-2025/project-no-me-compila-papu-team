#include "GuessNumberGame.h"
#include "SpriteDisplay.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

GuessNumberGame::GuessNumberGame() {
    srand(time(0));
}

bool GuessNumberGame::play() {
    clearScreen();
    cout << "\033[1;36m🎲 MINI-GAME: GUESS THE NUMBER\033[0m\n";
    cout << "I'm thinking of a number between 1 and 50.\n";
    cout << "You have 5 tries to guess it!\n\n";
    
    int secret = 1 + rand() % 50;
    int guess;
    int attempts = 5;
    
    for (int i = 1; i <= attempts; ++i) {
        cout << "Attempt " << i << "/" << attempts << ": Enter your guess (1-50): ";
        if (!(cin >> guess)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and 50.\n";
            --i;
            continue;
        }
        
        if (guess < 1 || guess > 50) {
            cout << "Please enter a number between 1 and 50.\n";
            --i;
            continue;
        }
        
        if (guess == secret) {
            cout << "\033[1;32m🎉 Correct! You win the mini-game!\033[0m\n";
            cout << "You found the number in " << i << " attempts.\n";
            cout << "\nPress any key to continue...";
            cin.ignore();
            cin.get();
            return true;
        } else if (guess < secret) {
            cout << "📈 Too low. Try a higher number.\n";
            if (i == attempts - 1) {
                cout << "💡 Hint: The number is between " << guess << " and 50.\n";
            }
        } else {
            cout << "📉 Too high. Try a lower number.\n";
            if (i == attempts - 1) {
                cout << "💡 Hint: The number is between 1 and " << guess << ".\n";
            }
        }
        
        if (i < attempts) {
            cout << "Press any key to continue...";
            cin.ignore();
            cin.get();
            clearScreen();
            cout << "\033[1;36m🎲 MINI-GAME: GUESS THE NUMBER\033[0m\n";
            cout << "Attempts remaining: " << (attempts - i) << "\n\n";
        }
    }
    
    cout << "\033[1;31m❌ You lost. The number was: " << secret << "\033[0m\n";
    cout << "\nPress any key to continue...";
    cin.ignore();
    cin.get();
    
    return false;
} 