#ifndef SPRITEDISPLAY_H
#define SPRITEDISPLAY_H

#include <string>
#include <vector>

void displayWelcomeMessage();
void displayMainMenu();
void displayDifficultyMenu();
void displayDifficultyRewards(char difficulty);
void displayProgressBar(int current, int total, int barWidth = 50);
void displayQuestionBox(const std::string& question, const std::vector<std::string>& options, int questionNumber, int totalQuestions, int score);
void displayCorrectAnswer();
void displayIncorrectAnswer(const std::string& correctAnswer);
void displayPowerUpMenu();
void displayMiniGameIntro(const std::string& gameName);
void displayFinalResults(const std::string& playerName, int score, int totalQuestions, int requiredToWin, int rewardLevel);
void displayHappySprite();
void displayAngrySprite();
void clearScreen();

// Hangman game display functions
void displayHangmanState(const std::string& hangmanArt, const std::string& guessedWord, const std::vector<char>& wrongGuesses, int attemptsLeft);
void displayHangmanMessage(const std::string& msg, const std::string& color = "\033[1;37m");

// RPS game display functions
void displayRPSRound(int round);
void displayRPSHands(const std::string* left, const std::string* right, int playerMove, int computerMove);
void displayRPSMessage(const std::string& msg, const std::string& color = "\033[1;37m");

// TicTacToe game display functions
void displayTicTacToeBoard(const std::vector<char>& board);
void displayTicTacToeMessage(const std::string& msg, const std::string& color = "\033[1;37m");

#endif