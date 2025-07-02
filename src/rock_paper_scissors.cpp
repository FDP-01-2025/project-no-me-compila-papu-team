#include "rock_paper_scissors.h"
#include <iostream>     // For input and output operations
#include <cstdlib>      // For random number generation (rand, srand)
#include <ctime>        // For seeding the random generator with time
#include <limits>

using namespace std;

// ASCII art for the left-facing ROCK hand
const string ROCK_LEFT[6] = {
    "    _______       ",
    "---'   ____)      ",
    "      (_____)     ",
    "      (_____)     ",
    "      (____)      ",
    "---.__(___)       "
};

// ASCII art for the left-facing PAPER hand
const string PAPER_LEFT[6] = {
    "     _______      ",
    "---'   ____)____  ",
    "          ______) ",
    "          _______)",
    "         _______) ",
    "---.__________)   "
};

// ASCII art for the left-facing SCISSORS hand
const string SCISSORS_LEFT[6] = {
    "     _______      ",
    "---'   ____)____  ",
    "          ______) ",
    "       __________)",
    "      (____)      ",
    "---.__(___)       "
};

// ASCII art for the right-facing ROCK hand
const string ROCK_RIGHT[6] = {
    "       _______    ",
    "      (____   '---",
    "     (_____)      ",
    "     (_____)      ",
    "      (____)      ",
    "       (___)__.---"
};

// ASCII art for the right-facing PAPER hand
const string PAPER_RIGHT[6] = {
    "      _______     ",
    "  ____(____   '---",
    " (______          ",
    "(_______          ",
    " (_______         ",
    "   (__________.---"
};

// ASCII art for the right-facing SCISSORS hand
const string SCISSORS_RIGHT[6] = {
    "      _______     ",
    "  ____(____   '---",
    " (______          ",
    "(__________       ",
    "      (____)      ",
    "       (___)__.---"
};

// ASCII art for the "VS" symbol between both hands
const string VS[6] = {
    " __      ____   ",
    " \\ \\    / ___|  ",
    "  \\ \\  | |___   ",
    "   \\ \\  \\___ \\  ",
    "    \\ \\ ___| |  ",
    "     \\_\\____/   "
};

RockPaperScissors::RockPaperScissors() {
    playerScore = 0;
    computerScore = 0;
    rounds = 0;
    srand(time(0));
}

void RockPaperScissors::displayRules() {
    cout << "\n🎯 ROCK, PAPER, SCISSORS - RULES 🎯" << endl;
    cout << "=====================================" << endl;
    cout << "• Rock (1) beats Scissors" << endl;
    cout << "• Paper (2) beats Rock" << endl;
    cout << "• Scissors (3) beats Paper" << endl;
    cout << "• Same choice = Tie" << endl;
    cout << "=====================================" << endl;
}

void RockPaperScissors::displayBattle(int player, int cpu) {
    const string* left;
    const string* right;

    // Assign appropriate ASCII hand to the player
    if (player == ROCK) left = ROCK_LEFT;
    else if (player == PAPER) left = PAPER_LEFT;
    else left = SCISSORS_LEFT;

    // Assign appropriate ASCII hand to the CPU
    if (cpu == ROCK) right = ROCK_RIGHT;
    else if (cpu == PAPER) right = PAPER_RIGHT;
    else right = SCISSORS_RIGHT;

    cout << "\n🎮 BATTLE SCENE 🎮" << endl;
    cout << "==================" << endl;
    
    // Display all 6 lines of both hands and the VS symbol
    for (int i = 0; i < 6; ++i) {
        cout << left[i] << "  " << VS[i] << "  " << right[i] << endl;
    }
    cout << "==================" << endl;
}

int RockPaperScissors::getComputerChoice() {
    return rand() % 3 + 1;
}

string RockPaperScissors::choiceToString(int choice) {
    switch (choice) {
        case ROCK: return "Rock";
        case PAPER: return "Paper";
        case SCISSORS: return "Scissors";
        default: return "Unknown";
    }
}

bool RockPaperScissors::isValidChoice(int choice) {
    return choice >= 1 && choice <= 3;
}

void RockPaperScissors::displayScore() {
    cout << "\n📊 CURRENT SCORE 📊" << endl;
    cout << "==================" << endl;
    cout << "Player: " << playerScore << " | Computer: " << computerScore << endl;
    cout << "==================" << endl;
}

void RockPaperScissors::playRound() {
    int playerChoice;
    int cpuChoice;
    
    cout << "\nChoose your weapon:" << endl;
    cout << "1. Rock" << endl;
    cout << "2. Paper" << endl;
    cout << "3. Scissors" << endl;
    cout << "Your choice (1-3): ";
    
    if (!(cin >> playerChoice)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number (1-3)." << endl;
        return;
    }
    
    if (!isValidChoice(playerChoice)) {
        cout << "Invalid choice. Please select 1, 2, or 3." << endl;
        return;
    }
    
    cpuChoice = getComputerChoice();
    
    cout << "\nYou chose: " << choiceToString(playerChoice) << endl;
    cout << "Computer chose: " << choiceToString(cpuChoice) << endl;
    
    displayBattle(playerChoice, cpuChoice);
    
    // Determine winner
    if (playerChoice == cpuChoice) {
        cout << "\n🤝 It's a TIE!" << endl;
    } else if ((playerChoice == ROCK && cpuChoice == SCISSORS) ||
               (playerChoice == PAPER && cpuChoice == ROCK) ||
               (playerChoice == SCISSORS && cpuChoice == PAPER)) {
        cout << "\n🎉 You WIN this round!" << endl;
        playerScore++;
    } else {
        cout << "\n😔 Computer wins this round!" << endl;
        computerScore++;
    }
    
    rounds++;
    displayScore();
}

void RockPaperScissors::displayFinalResults() {
    cout << "\n🏆 FINAL RESULTS 🏆" << endl;
    cout << "==================" << endl;
    cout << "Total Rounds: " << rounds << endl;
    cout << "Final Score - Player: " << playerScore << " | Computer: " << computerScore << endl;
    
    if (playerScore > computerScore) {
        cout << "🎉 CONGRATULATIONS! You are the WINNER! 🎉" << endl;
    } else if (computerScore > playerScore) {
        cout << "😔 Better luck next time! Computer wins!" << endl;
    } else {
        cout << "🤝 It's a TIE! Great match!" << endl;
    }
    cout << "==================" << endl;
}

void RockPaperScissors::startGame() {
    int choice;
    bool running = true;
    
    cout << "\n✂️ WELCOME TO ROCK, PAPER, SCISSORS! ✂️" << endl;
    displayRules();
    
    while (running) {
        cout << "\nChoose an option:" << endl;
        cout << "1. Play a round" << endl;
        cout << "2. View current score" << endl;
        cout << "3. View rules" << endl;
        cout << "4. Back to main menu" << endl;
        cout << "Your choice: ";
        
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number (1-4)." << endl;
            continue;
        }
        
        switch (choice) {
            case 1:
                playRound();
                break;
            case 2:
                displayScore();
                break;
            case 3:
                displayRules();
                break;
            case 4:
                if (rounds > 0) {
                    displayFinalResults();
                }
                cout << "Returning to main menu..." << endl;
                running = false;
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
                break;
        }
    }
}
