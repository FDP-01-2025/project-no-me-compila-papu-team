#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

// helper functions for input/output
void clearInputBuffer();
void displayWelcomeMessage();
void pauseScreen();

// functions for file stuff
std::vector<std::string> loadWordsFromFile(const std::string& filename);
void saveScoreToFile(const std::string& playerName, int score, const std::string& game);
void displayHighScores();
bool fileExists(const std::string& filename);
void createDefaultFiles();

// other utility functions
std::string getCurrentDateTime();
int generateRandomNumber(int min, int max);

#endif 