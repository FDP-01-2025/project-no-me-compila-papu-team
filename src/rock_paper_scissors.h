#ifndef ROCK_PAPER_SCISSORS_H
#define ROCK_PAPER_SCISSORS_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

class RockPaperScissors {
private:
    static const int ROCK = 1;
    static const int PAPER = 2;
    static const int SCISSORS = 3;
    
    int playerScore;
    int computerScore;
    int rounds;
    
    void displayBattle(int player, int cpu);
    void displayRules();
    void displayScore();
    int getComputerChoice();
    std::string choiceToString(int choice);
    bool isValidChoice(int choice);
    
public:
    RockPaperScissors();
    void startGame();
    void playRound();
    void displayFinalResults();
};

#endif // ROCK_PAPER_SCISSORS_H 