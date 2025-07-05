#include "rpgfight.h"
#include <iostream>
#include <limits>

using namespace std;

RpgFight::RpgFight() {
    difficulty = 1;
    // Initialize playerStats with default values
    playerStats.life = 0;
    playerStats.attack = 0;
    playerStats.defense = 0;
    playerStats.critticPercentage = 0;
}

void RpgFight::displaySprite() {
    cout << "                             /\\                        /\\" << endl;
    cout << "                            /||\\                      /||\\" << endl;
    cout << "                        ___/||||\\____________________/||||\\_____" << endl;
    cout << "                       /########################################\\" << endl;
    cout << "                      /######\\\\##########################//######\\" << endl;
    cout << "                      \\#######\\\\########################//#######/" << endl;
    cout << "                       \\#######\\\\######################//#######/" << endl;
    cout << "                        \\######################################/" << endl;
    cout << "                         \\####     ##################     ####/" << endl;
    cout << "                          \\### ||| ################## ||| ###/" << endl;
    cout << "                           \\## ||| ################## ||| ##/" << endl;
    cout << "                            \\##############################/" << endl;
    cout << "                           /#\\############################/#\\" << endl;
    cout << "                          |###\\##########################/###|" << endl;
    cout << "                         /|####\\########################/####|\\" << endl;
    cout << "                        /#|#####\\######################/#####|#\\" << endl;
    cout << "                       /##|######\\|||||||||VV|||||||||/######|##\\" << endl;
    cout << "                      /###|###################################|###\\" << endl;
    cout << "                     /####|###################################|####\\" << endl;
}

void RpgFight::setStats(int d) {
    if (d >= 1 && d <= 3) {
        switch (d) {
            case 1:
                playerStats.life = 150;
                playerStats.attack = 45;
                playerStats.defense = 40;
                playerStats.critticPercentage = 1;
                break;
            case 2:
                playerStats.life = 200;
                playerStats.attack = 60;
                playerStats.defense = 45;
                playerStats.critticPercentage = 5;
                break;
            case 3:
                playerStats.life = 260;
                playerStats.attack = 70;
                playerStats.defense = 50;
                playerStats.critticPercentage = 10;
                break;
        }
    }
}

void RpgFight::displayBattleScene() {
    cout << "|===================================|" << endl;
    cout << "| So, you finally came to my lair...|" << endl;
    cout << "|===================================|" << endl;
    cout << "" << endl;
    displaySprite();
    
    cout << "\nPlayer Stats:" << endl;
    cout << "Life: " << playerStats.life << endl;
    cout << "Attack: " << playerStats.attack << endl;
    cout << "Defense: " << playerStats.defense << endl;
    cout << "Critical Hit %: " << playerStats.critticPercentage << "%" << endl;
}

void RpgFight::displayMenu() {
    cout << "\n=== RPG FIGHT - CHOOSE YOUR DIFFICULTY ===" << endl;
    cout << "1. Easy (Beginner)" << endl;
    cout << "2. Medium (Intermediate)" << endl;
    cout << "3. Hard (Expert)" << endl;
    cout << "4. Back to Main Menu" << endl;
    cout << "Select difficulty: ";
}

void RpgFight::setDifficulty(int diff) {
    difficulty = diff;
    setStats(difficulty);
}

void RpgFight::startGame() {
    int choice;
    bool running = true;
    
    cout << "\n🎮 WELCOME TO RPG FIGHT! 🎮" << endl;
    cout << "Prepare for an epic battle!" << endl;
    
    while (running) {
        displayMenu();
        
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number (1-4)." << endl;
            continue;
        }
        
        switch (choice) {
            case 1:
            case 2:
            case 3:
                setDifficulty(choice);
                displayBattleScene();
                cout << "\nPress Enter to continue...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                break;
            case 4:
                cout << "Returning to main menu..." << endl;
                running = false;
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
                break;
        }
    }
}
    