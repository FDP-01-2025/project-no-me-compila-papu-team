#include "QuickReactionGame.h"
#include "SpriteDisplay.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;

QuickReactionGame::QuickReactionGame() {
    srand(time(0));
}

bool QuickReactionGame::play() {
    clearScreen();
    cout << "\033[1;36m⚡ MINI-GAME: QUICK REACTION\033[0m\n";
    cout << "When you see 'NOW', press ENTER as fast as you can.\n";
    cout << "Get ready...\n\n";
    
    // Random delay between 1-3 seconds
    int delay = 1000 + rand() % 2000;
    cout << "Waiting... ";
    for (int i = 3; i > 0; --i) {
        cout << i << " ";
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(delay / 3));
    }
    
    cout << "\n\nNOW!\n";
    auto start = chrono::high_resolution_clock::now();
    cin.ignore();
    cin.get();
    auto end = chrono::high_resolution_clock::now();
    double ms = chrono::duration<double, milli>(end - start).count();
    
    cout << "\nYour reaction time: " << ms << " ms\n";
    
    bool won = false;
    // More reasonable thresholds
    if (ms < 300) {
        cout << "\033[1;32m🏆 Amazing! Super fast reaction!\033[0m\n";
        cout << "You win the mini-game!\n";
        won = true;
    } else if (ms < 600) {
        cout << "\033[1;32m✅ Good reaction time!\033[0m\n";
        cout << "You win the mini-game!\n";
        won = true;
    } else if (ms < 1000) {
        cout << "\033[1;33m⚠️  Average reaction time.\033[0m\n";
        cout << "You win the mini-game!\n";
        won = true;
    } else {
        cout << "\033[1;31m🐌 Too slow. Try again next time.\033[0m\n";
        cout << "Reaction time should be under 1 second.\n";
        won = false;
    }
    
    cout << "\nPress any key to continue...";
    cin.ignore();
    cin.get();
    
    return won;
} 