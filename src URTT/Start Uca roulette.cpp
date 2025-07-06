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

int main() {
    srand(time(0));

    int playerLives = 4;
    int cpuLives = 4;

    while (playerLives > 0 && cpuLives > 0) {
        int liveCount = 0;
        int blankCount = 0;
        vector<bool> chamber = loadShotgun(liveCount, blankCount);
        int currentBullet = 0;

        cout << YELLOW << "\n=== NEW ROUND ===\n" << RESET;
        cout << "Bullets loaded: " << (liveCount + blankCount) << endl;
        cout << "Live bullets  : " << liveCount << endl;
        cout << "Blank bullets : " << blankCount << endl;

        while (playerLives > 0 && cpuLives > 0 && currentBullet < chamber.size()) {
            printStatus(playerLives, cpuLives);

            // === PLAYER TURN ===
            bool playerTurn = true;
            while (playerTurn && currentBullet < chamber.size() && playerLives > 0 && cpuLives > 0) {
                cout << "\nYour turn. Choose an option:\n";
                cout << "1. Shoot yourself\n";
                cout << "2. Shoot the CPU\n";
                cout << "Choice: ";

                int choice;
                cin >> choice;

                bool bullet = chamber[currentBullet];
                cout << "\nYou pulled the trigger..." << endl;

                this_thread::sleep_for(chrono::milliseconds(800));

                if (choice == 1) {
                    if (bullet) {
                        cout << RED << "💥 BOOM! You shot yourself!\n" << RESET;
                        playerLives--;
                        playerTurn = false;
                    } else {
                        cout << GREEN << "🔫 Click... it was blank. You get another turn!\n" << RESET;
                        playerTurn = true;
                    }
                } else if (choice == 2) {
                    if (bullet) {
                        cout << RED << "💥 BOOM! CPU takes the hit!\n" << RESET;
                        cpuLives--;
                    } else {
                        cout << GREEN << "🔫 Click... it was blank. CPU survives.\n" << RESET;
                    }
                    playerTurn = false;
                } else {
                    cout << "Invalid option. You lost your turn.\n";
                    playerTurn = false;
                }

                currentBullet++;
                this_thread::sleep_for(chrono::milliseconds(600));
            }
        }
    }

    return 0;
}
