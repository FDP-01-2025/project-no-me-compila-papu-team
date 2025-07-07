#include "ascii_art.h"  // Header file with ASCII art scene declarations

#include <iostream>     // For cin and cout
#include <vector>       // For using vector to store bullets
#include <cstdlib>      // For rand(), srand()
#include <ctime>        // For seeding randomness with time()
#include <algorithm>    // For random_shuffle()
#include <chrono>       // For time-based delays
#include <thread>       // For using sleep_for()

using namespace std;    // Avoid writing std:: in every line

// Terminal color codes for stylized output
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define CYAN    "\033[1;36m"
#define YELLOW  "\033[1;33m"
#define RESET   "\033[0m"  // Reset terminal color

// ---------------------------------------------------------
// Shows the game instructions and rules to the player
// ---------------------------------------------------------
void printRules() {
    cout << CYAN << "\n========== WELCOME TO UCA ROULETTE ==========\n\n" << RESET;

    // Brief explanation of the game
    cout << "This is a high-risk, quiz-themed Russian Roulette game.\n\n";

    // List of rules
    cout << YELLOW << "RULES:\n" << RESET;
    cout << "- You and the Owl (CPU) start with 4 lives each.\n";
    cout << "- The shotgun is loaded with 2 to 4 bullets each round.\n";
    cout << "- Bullets are randomly chosen to be live (BOOM!) or blank (click).\n";
    cout << "- On your turn, choose to:\n";
    cout << "    1. Shoot yourself\n";
    cout << "    2. Shoot the Owl\n";
    cout << "- A live bullet causes the target to lose a life.\n";
    cout << "- A blank gives you an extra turn ONLY if you shoot yourself.\n";
    cout << "- Turns alternate until someone runs out of lives.\n\n";

    // Victory message
    cout << GREEN << "WINNING:\n" << RESET;
    cout << "- If the Owl loses all lives first, you win!\n";
    cout << "- Winning may unlock a power-up in the next quiz round.\n\n";

    // Final message
    cout << CYAN << "Good luck... and aim wisely.\n" << RESET;

    this_thread::sleep_for(chrono::seconds(15)); // Pause to let player read
}

// ---------------------------------------------------------
// Simulates Owl (CPU) thinking before shooting
// ---------------------------------------------------------
void cpuThinking() {
    cout << "Owl is thinking";
    for (int i = 0; i < 3; ++i) {
        cout << ".";
        cout.flush(); // Ensures dot prints immediately
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    cout << endl;
}

// ---------------------------------------------------------
// Loads the shotgun with 2–4 bullets, mixed between live and blank
// Returns a vector<bool> representing the chamber
// ---------------------------------------------------------
vector<bool> loadShotgun(int& liveCount, int& blankCount) {
    vector<bool> chamber;
    liveCount = 0;
    blankCount = 0;

    do {
        chamber.clear();
        liveCount = 0;
        blankCount = 0;

        int numBullets = rand() % 3 + 2; // Random between 2 and 4

        for (int i = 0; i < numBullets; ++i) {
            bool isLive = rand() % 2;
            chamber.push_back(isLive);
            if (isLive) liveCount++;
            else blankCount++;
        }
    } while (liveCount == 0 || blankCount == 0); // Must have both types

    random_shuffle(chamber.begin(), chamber.end()); // Shuffle bullet order
    return chamber;
}

// ---------------------------------------------------------
// Displays current player and Owl lives with ASCII art
// ---------------------------------------------------------
void printStatus(int playerLives, int cpuLives) {
    cout << CYAN << "\n==================== STATUS ====================\n" << RESET;

    // Show player's life
    cout << YELLOW << "\nYour lives: " << playerLives << "\n" << RESET;
    if (playerLives == 4) Scene5_full_lives_for_one_or_both();
    else if (playerLives == 3) Scene4_three_lives_left_for_someone();
    else if (playerLives == 2) Scene3_two_lives_left_for_someone();
    else if (playerLives == 1) Scene2_one_life_left_for_someone();

    // Show Owl's life
    cout << YELLOW << "\nOwl lives: " << cpuLives << "\n" << RESET;
    if (cpuLives == 4) Scene5_full_lives_for_one_or_both();
    else if (cpuLives == 3) Scene4_three_lives_left_for_someone();
    else if (cpuLives == 2) Scene3_two_lives_left_for_someone();
    else if (cpuLives == 1) Scene2_one_life_left_for_someone();

    cout << CYAN << "\n================================================\n" << RESET;
}

// ---------------------------------------------------------
// Main game loop: alternates player and Owl turns until game ends
// ---------------------------------------------------------
int main() {
    srand(time(0));  // Initialize random seed

    int playerLives = 4;
    int cpuLives = 4;

    // Show logo and intro screens
    Scene18_uca_roulette_logo_screen();
    this_thread::sleep_for(chrono::seconds(2));
    Scene19_start_screen_game_begins();

    // Print rules before game starts
    printRules();

    // Game continues while both have lives
    while (playerLives > 0 && cpuLives > 0) {
        int liveCount = 0;
        int blankCount = 0;
        vector<bool> chamber = loadShotgun(liveCount, blankCount);
        int currentBullet = 0;

        // Start of round
        cout << YELLOW << "\n=== NEW ROUND ===\n" << RESET;
        cout << "Bullets loaded: " << (liveCount + blankCount) << endl;
        cout << "Live bullets  : " << liveCount << endl;
        cout << "Blank bullets : " << blankCount << endl;

        // Round loop: continues while there are bullets and both are alive
        while (playerLives > 0 && cpuLives > 0 && currentBullet < chamber.size()) {
            printStatus(playerLives, cpuLives);

            // ----------------- PLAYER TURN -----------------
            bool playerTurn = true;
            while (playerTurn && currentBullet < chamber.size() && playerLives > 0 && cpuLives > 0) {
                cout << "\nYour turn. Choose an option:\n";
                cout << "1. Shoot yourself\n";
                cout << "2. Shoot the Owl\n";
                cout << "Choice: ";

                int choice;
                cin >> choice;

                bool bullet = chamber[currentBullet];
                cout << "\nYou pulled the trigger..." << endl;
                this_thread::sleep_for(chrono::milliseconds(800));

                if (choice == 1) {
                    Scene12_player_chooses_to_shoot_self();
                    if (bullet) {
                        Scene16_loaded_shot_player_shoots_self_loses_life_turn_over();
                        cout << RED << " BOOM! You shot yourself!\n" << RESET;
                        playerLives--;
                        playerTurn = false;
                    } else {
                        Scene9_fake_shot_player_shoots_self_no_life_lost_has_extra_turn();
                        cout << GREEN << " Click... it was blank. You get another turn!\n" << RESET;
                        playerTurn = true;
                    }
                } else if (choice == 2) {
                    Scene13_player_chooses_to_shoot_owl();
                    if (bullet) {
                        Scene17_loaded_shot_player_hits_owl_owl_loses_life();
                        cout << RED << " BOOM! Owl takes the hit!\n" << RESET;
                        cpuLives--;
                    } else {
                        Scene14_fake_shot_owl_no_damage_player_turn_over();
                        cout << GREEN << " Click... it was blank. Owl survives.\n" << RESET;
                    }
                    playerTurn = false;
                } else {
                    cout << "Invalid option. You lost your turn.\n";
                    playerTurn = false;
                }

                currentBullet++;
                this_thread::sleep_for(chrono::milliseconds(600));
            }

            // ----------------- OWL TURN -----------------
            if (playerLives <= 0 || cpuLives <= 0 || currentBullet >= chamber.size()) break;

            bool cpuTurn = true;
            while (cpuTurn && currentBullet < chamber.size() && playerLives > 0 && cpuLives > 0) {
                cout << YELLOW << "\nOwl's turn...\n" << RESET;
                cpuThinking();

                int totalBullets = liveCount + blankCount;
                int bulletsLeft = totalBullets - currentBullet;

                // Count how many live bullets remain
                int livesLeft = 0;
                for (int i = currentBullet; i < totalBullets; ++i) {
                    if (chamber[i]) livesLeft++;
                }

                int blanksLeft = bulletsLeft - livesLeft;
                double risk = (double) livesLeft / bulletsLeft;

                int cpuChoice;
                if (risk >= 0.6) {
                    cpuChoice = 1; // Too risky to shoot itself
                } else {
                    cpuChoice = rand() % 2; // Random choice
                }

                bool bullet = chamber[currentBullet];

                if (cpuChoice == 0) {
                    Scene11_owl_chooses_to_shoot_self();
                    cout << "Owl aims at itself...\n";
                    this_thread::sleep_for(chrono::milliseconds(700));
                    if (bullet) {
                        Scene15_loaded_shot_owl_shoots_self_loses_life_turn_over();
                        cout << RED << " Owl shot itself!\n" << RESET;
                        cpuLives--;
                        cpuTurn = false;
                    } else {
                        Scene8_fake_shot_owl_shoots_self_no_life_lost_has_extra_turn();
                        cout << GREEN << " Click... Owl gets another turn!\n" << RESET;
                        cpuTurn = true;
                    }
                } else {
                    Scene10_owl_chooses_to_shoot_player();
                    cout << "Owl aims at you...\n";
                    this_thread::sleep_for(chrono::milliseconds(700));
                    if (bullet) {
                        Scene6_loaded_shot_owl_hits_player_loses_life();
                        cout << RED << " Owl shot you!\n" << RESET;
                        playerLives--;
                    } else {
                        Scene7_fake_shot_owl_hits_player_no_life_lost();
                        cout << GREEN << " Click... you survive.\n" << RESET;
                    }
                    cpuTurn = false;
                }

                currentBullet++;
                this_thread::sleep_for(chrono::milliseconds(600));
            }
        }
    }

    // --------------- FINAL RESULT AND RETURN CODE ---------------
    printStatus(playerLives, cpuLives);

    if (playerLives <= 0) {
        Scene1_one_of_them_died();
        cout << RED << "\nYou lost all your lives. Owl wins.\n" << RESET;
        return 1; // Player lost
    } else if (cpuLives <= 0) {
        Scene1_one_of_them_died();
        cout << GREEN << "\nOwl lost all its lives. You win!\n" << RESET;
        return 0; // Player won
    }
}


/*
===================== INTEGRATION NOTES FOR TEAM PAPU =====================

This program returns an exit code depending on the final result:
- return 0 → Player won the game
- return 1 → Player lost the game

This is useful if this file is called as a subprocess or module
from a larger system or main menu.

Example usage in another program:
-------------------------------------------------------------
int result = system("./uca_roulette");

if (result == 0) {
    // Player won → grant reward, power-up, next challenge, etc.
} else {
    // Player lost → maybe try again, or skip reward
}
-------------------------------------------------------------

=============================================================
*/
