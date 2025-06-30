#ifndef HANGMAN_H
#define HANGMAN_H

#include <string>
#include <vector>

class Hangman {
private:
    std::vector<std::string> words;
    std::string secretWord;
    std::string hiddenWord;
    std::vector<char> usedLetters;
    int remainingAttempts;
    int score;
    std::string playerName;
    static const int MAX_ATTEMPTS = 6;
    
    // functions for game logic
    void loadWords();
    void selectRandomWord();
    void initializeHiddenWord();
    void resetGame();
    
    // functions to display stuff
    void drawHangman();
    void showGameState();
    void showHiddenWord();
    void showUsedLetters();
    void showAttempts();
    
    // functions for input and game mechanics
    char getPlayerInput();
    bool isValidLetter(char letter);
    bool letterAlreadyUsed(char letter);
    bool letterInWord(char letter);
    void revealLetter(char letter);
    bool wordComplete();
    void processGuess(char letter);
    
    // functions for score and file stuff
    void calculateScore();
    void getPlayerName();
    void saveScore();
    
public:
    Hangman();
    void startGame();
    void playGame();
    void showGameMenu();
};

#endif 