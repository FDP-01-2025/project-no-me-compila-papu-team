#include "SuperTriviaGame.h"
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
    // Cargar preguntas de archivo al crear juego
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
    cout << "=== Welcome to the Super Trivia Game! ===\n";
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

        // Obtener 10 preguntas aleatorias de nivel
        auto questions = questionManager.getRandomQuestionsByLevel(level, totalQuestions);

        for (int i = 0; i < totalQuestions; ++i) {
            clearConsole();
            cout << "Question " << (i + 1) << " of " << totalQuestions << "\n";
            cout << "Score: " << correctAnswers << "\n\n";
            
            // Cada 3 preguntas, insertar minijuego
            if (i > 0 && i % 3 == 0) {
                bool wonMiniGame = miniGameHandler.playRandomMiniGame();
                if (wonMiniGame) {
                    clearConsole();
                    powerUp.choosePower();
                    applyPowerUpEffect();
                    clearConsole(); // Clear after power-up is applied
                } else {
                    clearConsole();
                    cout << "\nNo Power-Up earned. Continuing with trivia...\n";
                }
            }

            // Always show question info after mini-games or at start
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
                int pointsToAdd = 1;
                if (doublePointsActive) pointsToAdd = 2;
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
                    // Redisplay the question for the extra life attempt
                    clearConsole();
                    cout << "Question " << (i + 1) << " of " << totalQuestions << "\n";
                    cout << "Score: " << correctAnswers << "\n\n";
                    questions[i].display(reducedOptionsActive, revealHintActive);
                    cout << "Your answer: ";
                    cin >> answer;
                    answer = toupper(answer);
                    if (questions[i].checkAnswer(answer)) {
                        cout << "Correct!\n";
                        int pointsToAdd = 1;
                        if (doublePointsActive) pointsToAdd = 2;
                        correctAnswers += pointsToAdd;
                    } else {
                        cout << "Still incorrect.\n";
                        cout << "The correct answer was: " << questions[i].getCorrectAnswer() << "\n";
                    }
                    cout << "Press any key to continue...";
                    cin.ignore();
                    cin.get();
                    // Extra life used once, deactivate it
                    extraLifeActive = false;
                } else {
                    cout << "Press any key to continue...";
                    cin.ignore();
                    cin.get();
                }
            }

            // Deactivate power-ups after each question
            if (doublePointsActive) doublePointsActive = false;
            if (reducedOptionsActive) reducedOptionsActive = false;
            if (revealHintActive) revealHintActive = false;
        }

        showFinalResults();
        askPlayAgain(playAgain);
    }

    cout << "\nThanks for playing! Goodbye!\n";
}