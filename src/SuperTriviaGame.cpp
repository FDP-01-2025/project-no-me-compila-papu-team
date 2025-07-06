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

    player.inputPlayerInfo();

    bool playAgain = true;
    while (playAgain) {
        clearConsole();
        resetPowerUps();
        correctAnswers = 0;

        char level;
        cout << "\nSelect difficulty level: (F) Easy, (M) Medium, (A) Advanced: ";
        cin >> level;
        level = toupper(level);

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

            cout << "Your answer: ";
            char answer;
            cin >> answer;
            answer = toupper(answer);

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
                    cout << "Your answer: ";
                    cin >> answer;
                    answer = toupper(answer);
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