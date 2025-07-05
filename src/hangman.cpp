#include "hangman.h"
#include "utils.h"
#include <iostream>
#include <algorithm>
#include <limits>

using namespace std;

// constructor - sets up the game
Hangman::Hangman() : remainingAttempts(MAX_ATTEMPTS), score(0) {
    createDefaultFiles();
    loadWords();
}

void Hangman::loadWords() {
    words = loadWordsFromFile("src/game_data/words.txt");
}

void Hangman::selectRandomWord() {
    if (words.empty()) {
        cout << "Error: No words available for the game.\n";
        return;
    }
    int randomIndex = generateRandomNumber(0, words.size() - 1);
    secretWord = words[randomIndex];
}

// sets up the hidden word with underscores
void Hangman::initializeHiddenWord() {
    hiddenWord = string(secretWord.length(), '_');
}

void Hangman::resetGame() {
    selectRandomWord();
    initializeHiddenWord();
    usedLetters.clear();
    remainingAttempts = MAX_ATTEMPTS;
    score = 0;
}

// draws the hangman based on wrong guesses
void Hangman::drawHangman() {
    cout << "\n";
    cout << "  +---+\n";
    cout << "  |   |\n";
    
    // draw head
    if (remainingAttempts < 6) {
        cout << "  O   |\n";
    } else {
        cout << "      |\n";
    }
    
    // draw body and arms
    if (remainingAttempts < 4) {
        cout << " /|\\  |\n";  // both arms
    } else if (remainingAttempts < 5) {
        cout << " /|   |\n";  // left arm
    } else if (remainingAttempts < 6) {
        cout << "  |   |\n";  // just body
    } else {
        cout << "      |\n";
    }
    
    // draw legs
    if (remainingAttempts < 2) {
        cout << " / \\  |\n";  // both legs - game over!
    } else if (remainingAttempts < 3) {
        cout << " /    |\n";  // one leg
    } else {
        cout << "      |\n";
    }
    
    cout << "      |\n";
    cout << "=========\n";
}

void Hangman::showHiddenWord() {
    cout << "\nWord: ";
    for (char c : hiddenWord) {
        cout << c << " ";
    }
    cout << "\n";
}

void Hangman::showUsedLetters() {
    cout << "Used letters: ";
    for (char c : usedLetters) {
        cout << c << " ";
    }
    cout << "\n";
}

void Hangman::showAttempts() {
    cout << "Remaining attempts: " << remainingAttempts << "/" << MAX_ATTEMPTS << "\n";
}

void Hangman::showGameState() {
    drawHangman();
    showHiddenWord();
    showUsedLetters();
    showAttempts();
}

char Hangman::getPlayerInput() {
    char letter;
    cout << "\nEnter a letter: ";
    cin >> letter;
    return toupper(letter);
}

bool Hangman::isValidLetter(char letter) {
    return isalpha(letter);
}

bool Hangman::letterAlreadyUsed(char letter) {
    return find(usedLetters.begin(), usedLetters.end(), letter) != usedLetters.end();
}

bool Hangman::letterInWord(char letter) {
    return secretWord.find(letter) != string::npos;
}

void Hangman::revealLetter(char letter) {
    for (size_t i = 0; i < secretWord.length(); i++) {
        if (secretWord[i] == letter) {
            hiddenWord[i] = letter;
        }
    }
}

bool Hangman::wordComplete() {
    return hiddenWord == secretWord;
}

// processes player's letter guess
void Hangman::processGuess(char letter) {
    // check if it's actually a letter
    if (!isValidLetter(letter)) {
        cout << "Please enter a valid letter.\n";
        return;
    }
    
    // check if already tried this letter
    if (letterAlreadyUsed(letter)) {
        cout << "You already used that letter. Try another one.\n";
        return;
    }
    
    // add to used letters list
    usedLetters.push_back(letter);
    
    // check if letter is in the word
    if (letterInWord(letter)) {
        cout << "Correct! The letter '" << letter << "' is in the word.\n";
        revealLetter(letter);
        score += 10; // give points for right answer
    } else {
        cout << "Incorrect. The letter '" << letter << "' is not in the word.\n";
        remainingAttempts--;
        score = max(0, score - 5); // lose some points
    }
}

// calculates final score based on performance
void Hangman::calculateScore() {
    score += remainingAttempts * 5; // bonus for attempts left
    score += secretWord.length() * 2; // bonus for longer words
}

void Hangman::getPlayerName() {
    cout << "\nEnter your name for the high score: ";
    cin.ignore();
    getline(cin, playerName);
    if (playerName.empty()) {
        playerName = "Anonymous";
    }
}

void Hangman::saveScore() {
    if (score > 0) {
        getPlayerName();
        saveScoreToFile(playerName, score, "Hangman");
    }
}

void Hangman::playGame() {
    cout << "\n=== HANGMAN GAME ===\n";
    cout << "Guess the word before the hangman is completed!\n";
    
    while(remainingAttempts > 0 && !wordComplete()) {
        showGameState();
        char letter = getPlayerInput();
        processGuess(letter);
        cout << "\n" << string(50, '-') << "\n";
    }
    
    // Show final result
    showGameState();
    
    if (wordComplete()) {
        cout << "\n*** CONGRATULATIONS! YOU WON! ***\n";
        cout << "You guessed the word: " << secretWord << "\n";
        calculateScore();
        cout << "Your score: " << score << " points\n";
        saveScore();
    } else {
        cout << "\n*** GAME OVER! You lost. ***\n";
        cout << "The word was: " << secretWord << "\n";
        score = 0;
    }
}

void Hangman::showGameMenu() {
    while (true) {
        cout << "\n=== HANGMAN MENU ===\n";
        cout << "1. Play Game\n";
        cout << "2. Back to Main Menu\n";
        cout << "Select an option: ";
        
        int option;
        cin >> option;
        
        if (cin.fail()) {
            clearInputBuffer();
            cout << "Invalid option. Try again.\n";
            continue;
        }
        
        switch (option) {
            case 1:
                resetGame();
                playGame();
                break;
            case 2:
                return;
            default:
                cout << "Invalid option. Try again.\n";
                break;
        }
    }
}

void Hangman::startGame() {
    showGameMenu();
} 