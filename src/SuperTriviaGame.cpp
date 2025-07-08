#include "SuperTriviaGame.h"
#include "SpriteDisplay.h"
#include <iostream>
#include <cctype>

using namespace std;

void clearConsole() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

SuperTriviaGame::SuperTriviaGame() : correctAnswers(0), totalQuestions(10),
    doublePointsActive(false), reducedOptionsActive(false),
    extraLifeActive(false), revealHintActive(false)
{
    if (!questionManager.loadFromFile("trivia_data.txt")) {
        cout << "Error loading trivia questions file!\n";
    }
}

void SuperTriviaGame::resetPowerUps() {
    doublePointsActive = false;
    reducedOptionsActive = false;
    extraLifeActive = false;
    revealHintActive = false;
}

void SuperTriviaGame::applyPowerUpEffect() {
    switch (powerUp.getType()) {
        case DOUBLE_POINTS: doublePointsActive = true; break;
        case REDUCED_OPTIONS: reducedOptionsActive = true; break;
        case EXTRA_LIFE: extraLifeActive = true; break;
        case REVEAL_HINT: revealHintActive = true; break;
        default: break;
    }
    powerUp.applyEffect();
}

void SuperTriviaGame::showFinalResults() {
    clearConsole();
    cout << "\n=== ROUND COMPLETED ===\n";
    cout << "Player: " << player.getFullName() << "\n";
    cout << "Score: " << correctAnswers << " out of " << totalQuestions << "\n";

    if (correctAnswers >= totalQuestions / 2) {
        displayHappySprite();
    } else {
        displayAngrySprite();
    }

    player.setScore(correctAnswers);
    player.saveScore();

    cout << "\nDo you want to play again? (Y/N): ";
}

void SuperTriviaGame::askPlayAgain(bool &playAgain) {
    char choice;
    while (true) {
        cin >> choice;
        choice = toupper(choice);
        if (choice == 'Y') {
            playAgain = true;
            break;
        }
        else if (choice == 'N') {
            playAgain = false;
            break;
        }
        else {
            cout << "Please enter Y or N: ";
        }
    }
}

void SuperTriviaGame::start() {
    clearConsole();
    displayWelcomeMessage();
    cin.ignore();
    cin.get(); // Espera que el jugador presione una tecla
    clearConsole();

    // Mostrar opciones del menú principal
    char menuChoice;
    while (true) {
        cout << "\n============================================================\n";
        cout << "                    MAIN MENU\n";
        cout << "============================================================\n";
        cout << "1. Play Game - Start your journey to stop being poor!\n";
        cout << "2. View Saved Scores - Check your progress\n";
        cout << "3. Exit - Leave the game\n";
        cout << "------------------------------------------------------------\n";
        cout << "Enter your choice (1-3): ";
        cin >> menuChoice;
        
        if (menuChoice == '1') {
            break;
        } else if (menuChoice == '2') {
            clearConsole();
            Player::displaySavedScores();
            clearConsole();
        } else if (menuChoice == '3') {
            cout << "\nThanks for playing! Keep learning and stop being poor!\n";
            return;
        } else {
            cout << "Invalid choice. Please enter 1, 2, or 3.\n";
        }
    }

    player.inputPlayerInfo();

    bool playAgain = true;
    while (playAgain) {
        clearConsole();
        resetPowerUps();
        correctAnswers = 0;

    char level;
while (true) {
    cout << "\nSelect difficulty level:\n";
    cout << "F - Easy\nM - Medium\nA - Advanced\n";
    cout << "Enter your choice: ";
    cin >> level;
    level = toupper(level);

    if (level == 'F' || level == 'M' || level == 'A') { 
        break;
    } else {
        cout << "Invalid input. Please enter F, M, or A.\n\n";
    }
}

auto questions = questionManager.getRandomQuestionsByLevel(level, totalQuestions);

        for (int i = 0; i < totalQuestions; ++i) {
            clearConsole();
            cout << "Question " << (i + 1) << " of " << totalQuestions << "\n";
            cout << "Score: " << correctAnswers << "\n\n";

            if (i > 0 && i % 3 == 0) {
                bool wonMiniGame = miniGameHandler.playRandomMiniGame();
                if (wonMiniGame) {
                    clearConsole();
                    powerUp.choosePower();
                    applyPowerUpEffect();
                    clearConsole();
                } else {
                    clearConsole();
                    cout << "\nNo Power-Up earned. Continuing with trivia...\n";
                }
            }

            clearConsole();
            cout << "Question " << (i + 1) << " of " << totalQuestions << "\n";
            cout << "Score: " << correctAnswers << "\n\n";

            questions[i].display(reducedOptionsActive, revealHintActive);

            char answer;
            bool validAnswer = false;
            while (!validAnswer) {
                cout << "Your answer: ";
                cin >> answer;
                answer = toupper(answer);
                
                // Validar que la respuesta sea una opción válida (A, B, C, D)
                if (answer == 'A' || answer == 'B' || answer == 'C' || answer == 'D') {
                    validAnswer = true;
                } else {
                    cout << "Invalid option. Please enter A, B, C, or D.\n";
                }
            }

            if (questions[i].checkAnswer(answer)) {
                clearConsole();
                cout << "Correct!\n";
                int pointsToAdd = doublePointsActive ? 2 : 1;
                if (doublePointsActive) {
                    cout << "DOUBLE POINTS! +" << pointsToAdd << " points\n";
                }
                correctAnswers += pointsToAdd;
                cout << "Press any key to continue...";
                cin.ignore();
                cin.get();
            } else {
                clearConsole();
                cout << "Incorrect.\n";
                cout << "The correct answer was: " << questions[i].getCorrectAnswer() << "\n";
                if (extraLifeActive) {
                    cout << "You have an extra life! Try again: ";
                    clearConsole();
                    cout << "Question " << (i + 1) << " of " << totalQuestions << "\n";
                    cout << "Score: " << correctAnswers << "\n\n";
                    questions[i].display(reducedOptionsActive, revealHintActive);
                    
                    validAnswer = false;
                    while (!validAnswer) {
                        cout << "Your answer: ";
                        cin >> answer;
                        answer = toupper(answer);
                        
                        // Validar que la respuesta sea una opción válida (A, B, C, D)
                        if (answer == 'A' || answer == 'B' || answer == 'C' || answer == 'D') {
                            validAnswer = true;
                        } else {
                            cout << "Invalid option. Please enter A, B, C, or D.\n";
                        }
                    }
                    if (questions[i].checkAnswer(answer)) {
                        cout << "Correct!\n";
                        int pointsToAdd = doublePointsActive ? 2 : 1;
                        if (doublePointsActive) {
                            cout << "DOUBLE POINTS! +" << pointsToAdd << " points\n";
                        }
                        correctAnswers += pointsToAdd;
                    } else {
                        cout << "Still incorrect.\n";
                        cout << "The correct answer was: " << questions[i].getCorrectAnswer() << "\n";
                    }
                    cout << "Press any key to continue...";
                    cin.ignore();
                    cin.get();
                    extraLifeActive = false;
                } else {
                    cout << "Press any key to continue...";
                    cin.ignore();
                    cin.get();
                }
            }

            doublePointsActive = false;
            reducedOptionsActive = false;
            revealHintActive = false;
        }

        showFinalResults();
        askPlayAgain(playAgain);
    }

    cout << "\nThanks for playing! Goodbye!\n";
}