#include "MemorySequenceGame.h"
#include "SpriteDisplay.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <limits>

using namespace std;

MemorySequenceGame::MemorySequenceGame() {
    srand(time(0));
}

bool MemorySequenceGame::play() {
    clearScreen();
    cout << "\033[1;36m🧠 MINI-GAME: MEMORY SEQUENCE\033[0m\n";
    cout << "Memorize the following sequence of numbers.\n";
    cout << "You will have 3 seconds to memorize it.\n\n";
    
    vector<int> sequence;
    int length = 5 + rand() % 3; // Sequence of 5 to 7 numbers
    for (int i = 0; i < length; ++i) sequence.push_back(rand() % 10);
    
    cout << "Sequence: ";
    for (int n : sequence) cout << n << " ";
    cout << endl;
    
    cout << "\nMemorizing... ";
    for (int i = 3; i > 0; --i) {
        cout << i << " ";
        cout.flush();
        this_thread::sleep_for(chrono::seconds(1));
    }
    cout << "GO!\n";
    
    clearScreen();
    cout << "Enter the sequence (space separated): ";
    cout << "Example: 1 2 3 4 5\n";
    cout << "Your input: ";
    
    vector<int> userSeq;
    int num;
    bool validInput = true;
    
    for (int i = 0; i < length; ++i) {
        if (!(cin >> num)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter numbers only.\n";
            validInput = false;
            break;
        }
        if (num < 0 || num > 9) {
            cout << "Invalid number. Please enter digits 0-9 only.\n";
            validInput = false;
            break;
        }
        userSeq.push_back(num);
    }
    
    bool won = false;
    if (!validInput || userSeq.size() != length) {
        cout << "\033[1;31m❌ Invalid input format. You lose.\033[0m\n";
        cout << "The sequence was: ";
        for (int n : sequence) cout << n << " ";
        cout << "\n";
        won = false;
    } else if (userSeq == sequence) {
        cout << "\033[1;32m🎉 Correct! You win the mini-game!\033[0m\n";
        cout << "Perfect memory!\n";
        won = true;
    } else {
        cout << "\033[1;31m❌ Incorrect. The sequence was: ";
        for (int n : sequence) cout << n << " ";
        cout << "\033[0m\n";
        cout << "You entered: ";
        for (int n : userSeq) cout << n << " ";
        cout << "\n";
        won = false;
    }
    
    cout << "\nPress any key to continue...";
    cin.ignore();
    cin.get();
    
    return won;
} 