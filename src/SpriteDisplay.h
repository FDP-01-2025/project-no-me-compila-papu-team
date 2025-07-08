#ifndef SPRITEDISPLAY_H
#define SPRITEDISPLAY_H

#include <string>
#include <vector>

void displayWelcomeMessage();
void displayMainMenu();
void displayDifficultyMenu();
void displayProgressBar(int current, int total, int barWidth = 50);
void displayQuestionBox(const std::string& question, const std::vector<std::string>& options, int questionNumber, int totalQuestions, int score);
void displayCorrectAnswer();
void displayIncorrectAnswer(const std::string& correctAnswer);
void displayPowerUpMenu();
void displayMiniGameIntro(const std::string& gameName);
void displayFinalResults(const std::string& playerName, int score, int totalQuestions);
void displayHappySprite();
void displayAngrySprite();
void clearScreen();

#endif