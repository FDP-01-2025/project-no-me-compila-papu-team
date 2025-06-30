#include "utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <algorithm>

using namespace std;

// clears input buffer when user enters wrong stuff
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void displayWelcomeMessage() {
    cout << R"(
 ╔═══════════════════════════════════════════════════════════════════════════════════╗
 ║                    ¿QUIÉN QUIERE DEJAR DE SER POBRE?                            ║
 ║                           Game Collection                                        ║
 ╚═══════════════════════════════════════════════════════════════════════════════════╝
     
      🎮 Welcome to our exciting game collection! 🎮
      💰 Play games, earn points, and stop being poor in knowledge! 💰

)" << endl;
    cout << "Developed in C++ - Console Games Collection\n\n";
}

void pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

// function to load words from txt file
vector<string> loadWordsFromFile(const string& filename) {
    vector<string> words;
    ifstream file(filename);
    
    // if file doesn't exist, use some default words
    if (!file.is_open()) {
        cout << "Warning: Could not open " << filename << ". Using default words.\n";
        return {"PROGRAMMING", "COMPUTER", "ALGORITHM", "VARIABLE", "FUNCTION",
                "CLASS", "OBJECT", "INHERITANCE", "POLYMORPHISM", "ENCAPSULATION"};
    }
    
    string word;
    // read each line from file
    while (getline(file, word)) {
        if (!word.empty()) {
            // make everything uppercase
            transform(word.begin(), word.end(), word.begin(), ::toupper);
            words.push_back(word);
        }
    }
    
    file.close();
    
    // just in case file was empty
    if (words.empty()) {
        cout << "Warning: No words found in file. Using default words.\n";
        return {"PROGRAMMING", "COMPUTER", "ALGORITHM", "VARIABLE", "FUNCTION"};
    }
    
    return words;
}

// saves player score to file
void saveScoreToFile(const string& playerName, int score, const string& game) {
    ofstream file("src/game_data/scores.txt", ios::app); // append mode
    
    if (!file.is_open()) {
        cout << "Error: Could not save score to file.\n";
        return;
    }
    
    // write score with date and time
    file << getCurrentDateTime() << " | " << game << " | " << playerName << " | " << score << endl;
    file.close();
    
    cout << "Score saved successfully!\n";
}

void displayHighScores() {
    ifstream file("src/game_data/scores.txt");
    
    if (!file.is_open()) {
        cout << "No high scores found yet. Play some games to create scores!\n";
        return;
    }
    
    cout << "\n====== HIGH SCORES ======\n";
    cout << "Date & Time          | Game     | Player   | Score\n";
    cout << "----------------------------------------------------\n";
    
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
    
    file.close();
    pauseScreen();
}

bool fileExists(const string& filename) {
    ifstream file(filename);
    return file.good();
}

// creates default files if they don't exist
void createDefaultFiles() {
    // create words file with some programming words
    if (!fileExists("src/game_data/words.txt")) {
        ofstream wordsFile("src/game_data/words.txt");
        if (wordsFile.is_open()) {
            // add some words related to programming
            wordsFile << "PROGRAMMING\n";
            wordsFile << "COMPUTER\n";
            wordsFile << "ALGORITHM\n";
            wordsFile << "VARIABLE\n";
            wordsFile << "FUNCTION\n";
            wordsFile << "CLASS\n";
            wordsFile << "OBJECT\n";
            wordsFile << "INHERITANCE\n";
            wordsFile << "POLYMORPHISM\n";
            wordsFile << "ENCAPSULATION\n";
            wordsFile << "INTERFACE\n";
            wordsFile << "ABSTRACT\n";
            wordsFile << "EXCEPTION\n";
            wordsFile << "RECURSION\n";
            wordsFile << "ITERATION\n";
            wordsFile << "ARRAY\n";
            wordsFile << "MATRIX\n";
            wordsFile << "POINTER\n";
            wordsFile << "REFERENCE\n";
            wordsFile << "TEMPLATE\n";
            wordsFile.close();
        }
    }
    
    // create empty scores file
    if (!fileExists("src/game_data/scores.txt")) {
        ofstream scoresFile("src/game_data/scores.txt");
        if (scoresFile.is_open()) {
            scoresFile << "# Game Scores Log\n";
            scoresFile << "# Format: Date | Game | Player | Score\n";
            scoresFile.close();
        }
    }
}

// gets current date and time as string
string getCurrentDateTime() {
    time_t now = time(0);
    char* dt = ctime(&now);
    string dateTime = string(dt);
    dateTime.pop_back(); // remove the \n at the end
    return dateTime;
}

// generates random number between min and max
int generateRandomNumber(int min, int max) {
    static bool seeded = false;
    if (!seeded) {
        srand(time(0)); // seed only once
        seeded = true;
    }
    return min + rand() % (max - min + 1);
} 