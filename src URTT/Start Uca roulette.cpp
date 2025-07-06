#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono>
#include <thread>

using namespace std;

// ASCII escape codes for colors
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define CYAN    "\033[1;36m"
#define YELLOW  "\033[1;33m"
#define RESET   "\033[0m"

// Function to simulate CPU "thinking..."
void cpuThinking() {
    cout << "CPU is thinking";
    for (int i = 0; i < 3; ++i) {
        cout << ".";
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    cout << endl;
}

// Function to shuffle and load the shotgun with mixed bullets
vector<bool> loadShotgun(int& liveCount, int& blankCount) {
    vector<bool> chamber;
    liveCount = 0;
    blankCount = 0;

    do {
        chamber.clear();
        liveCount = 0;
        blankCount = 0;
        int numBullets = rand() % 3 + 2; // Between 2 and 4

        for (int i = 0; i < numBullets; ++i) {
            bool isLive = rand() % 2; // 0 = blank, 1 = live
            chamber.push_back(isLive);
            if (isLive) liveCount++;
            else blankCount++;
        }
    } while (liveCount == 0 || blankCount == 0); // Retry if all are same

    random_shuffle(chamber.begin(), chamber.end());
    return chamber;
}

// Function to display current life status
void printStatus(int playerLives, int cpuLives) {
    cout << CYAN << "\n--------------------------------\n";
    cout << "Your lives: " << playerLives << endl;
    cout << "CPU lives : " << cpuLives << endl;
    cout << "--------------------------------\n" << RESET;
}
