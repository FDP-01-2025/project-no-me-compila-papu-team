#include <iostream>     // For input and output operations
#include <cstdlib>      // For random number generation (rand, srand)
#include <ctime>        // For seeding the random generator with time
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

// Function to display the battle scene between player and CPU
void displayBattle(int player, int cpu) {
    const string* left;
    const string* right;

    // Assign appropriate ASCII hand to the player
    if (player == 1) left = ROCK_LEFT;
    else if (player == 2) left = PAPER_LEFT;
    else left = SCISSORS_LEFT;

    // Assign appropriate ASCII hand to the CPU
    if (cpu == 1) right = ROCK_RIGHT;
    else if (cpu == 2) right = PAPER_RIGHT;
    else right = SCISSORS_RIGHT;

    // Display all 6 lines of both hands and the VS symbol
    for (int i = 0; i < 6; ++i) {
        cout << left[i] << "  " << VS[i] << "  " << right[i] << endl;
    }
}

int main() {
    srand(time(0)); // Seed the random number generator

    int playerChoice; // Stores the player's choice
    int cpuChoice;    // Stores the CPU's choice

    // Print the game menu
    cout << "1. Rock\n2. Paper\n3. Scissors\n";
    cout << "Choose (1-3): ";
    cin >> playerChoice;

    // Validate input
    if (playerChoice < 1 || playerChoice > 3) {
        cout << "Invalid input.\n";
        return 0;
    }

    // Generate a random choice for the CPU (1 to 3)
    cpuChoice = rand() % 3 + 1;

    // Display the ASCII battle scene
    displayBattle(playerChoice, cpuChoice);

    return 0;
}
