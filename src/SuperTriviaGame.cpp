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

SuperTriviaGame::SuperTriviaGame() : correctAnswers(0), totalQuestions(10), requiredToWin(7),
    doublePointsActive(false), reducedOptionsActive(false),
    extraLifeActive(false), revealHintActive(false), rewardLevel(0)
{
    if (!questionManager.loadFromFile("data/trivia_data.txt")) {
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
    calculateReward();
    displayFinalResults(player.getFullName(), correctAnswers, totalQuestions, requiredToWin, rewardLevel);
    offerRevengeGame();
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

void SuperTriviaGame::calculateReward() {
    if (correctAnswers >= 10) {
        rewardLevel = 3;  // Chocolate bar
    } else if (correctAnswers >= 7) {
        rewardLevel = 2;  // 2 small chocolates
    } else if (correctAnswers >= 4) {
        rewardLevel = 1;  // 1 small chocolate
    } else {
        rewardLevel = 0;  // No reward
    }
}

void SuperTriviaGame::offerRevengeGame() {
    if (correctAnswers < requiredToWin && correctAnswers >= 4) {
        cout << "\n╔══════════════════════════════════════════════════════════════════════════════╗\n";
        cout << "║                              🎲 REVENGE GAME 🎲                              ║\n";
        cout << "╠══════════════════════════════════════════════════════════════════════════════╣\n";
        cout << "║                                                                              ║\n";
        cout << "║  🎯 You didn't reach the minimum score, but you can try a revenge game!    ║\n";
        cout << "║  🏆 Win to get a better reward! Lose and get nothing!                      ║\n";
        cout << "║                                                                              ║\n";
        cout << "╚══════════════════════════════════════════════════════════════════════════════╝\n";
        cout << "\nDo you want to play the revenge game? (Y/N): ";
        
        char choice;
        cin >> choice;
        choice = toupper(choice);
        
        if (choice == 'Y') {
            bool wonRevenge = miniGameHandler.playRandomMiniGame();
            if (wonRevenge) {
                cout << "\n🎉 You won the revenge game! Your reward has been upgraded!\n";
                if (rewardLevel == 1) rewardLevel = 2;
                else if (rewardLevel == 0) rewardLevel = 1;
            } else {
                cout << "\n❌ You lost the revenge game. No reward for you!\n";
                rewardLevel = 0;
            }
        }
    }
}

void SuperTriviaGame::start() {
    clearConsole();
    displayWelcomeMessage();
    cin.ignore();
    cin.get(); // Wait for the player to press a key
    clearConsole();

    // Show main menu options
    char menuChoice;
    while (true) {
        displayMainMenu();
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

    clearScreen();
    player.inputPlayerInfo();

    bool playAgain = true;
    while (playAgain) {
        clearConsole();
        resetPowerUps();
        correctAnswers = 0;

        displayDifficultyMenu();
        char level;
        while (true) {
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
            if (i > 0 && i % 3 == 0) {
                bool wonMiniGame = miniGameHandler.playRandomMiniGame();
                if (wonMiniGame) {
                    clearConsole();
                    displayPowerUpMenu();
                    powerUp.choosePower();
                    applyPowerUpEffect();
                    clearConsole();
                } else {
                    clearConsole();
                    cout << "\nNo Power-Up earned. Continuing with trivia...\n";
                }
            }

            // Show question with new interface
            clearConsole();
            displayProgressBar(i + 1, totalQuestions);
            
            cout << "\n╔══════════════════════════════════════════════════════════════════════════════╗\n";
            cout << "║                              🧠 PREGUNTA " << (i + 1) << "/" << totalQuestions << " 🧠                          ║\n";
            cout << "║                              📊 Score: " << correctAnswers << " points 📊                        ║\n";
            cout << "╠══════════════════════════════════════════════════════════════════════════════╣\n";
            cout << "║                                                                              ║\n";
            
            // Show question with formatted output
            cout << "║  " << questions[i].question << "\n";
            cout << "║                                                                              ║\n";
            
            // Show options with improved formatting
            char optionLetters[] = {'A', 'B', 'C', 'D'};
            for (int j = 0; j < questions[i].options.size(); j++) {
                cout << "║  🎯 " << optionLetters[j] << ") " << questions[i].options[j];
                // Fill spaces to keep alignment
                int spaces = 70 - questions[i].options[j].length();
                for (int k = 0; k < spaces; k++) cout << " ";
                cout << " ║\n";
            }
            
            cout << "║                                                                              ║\n";
            cout << "╚══════════════════════════════════════════════════════════════════════════════╝\n";
            cout << "\n🎯 Tu respuesta (A/B/C/D): ";

            char answer;
            bool validAnswer = false;
            while (!validAnswer) {
                cin >> answer;
                answer = toupper(answer);
                
                // Validate that the answer is a valid option (A, B, C, D)
                if (answer == 'A' || answer == 'B' || answer == 'C' || answer == 'D') {
                    validAnswer = true;
                } else {
                    cout << "Invalid option. Please enter A, B, C, or D.\n";
                }
            }

            if (questions[i].checkAnswer(answer)) {
                displayCorrectAnswer();
                int pointsToAdd = doublePointsActive ? 2 : 1;
                if (doublePointsActive) {
                    cout << "DOUBLE POINTS! +" << pointsToAdd << " points\n";
                }
                correctAnswers += pointsToAdd;
                cin.ignore();
                cin.get();
            } else {
                displayIncorrectAnswer(questions[i].getCorrectAnswer());
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
                        
                        // Validate that the answer is a valid option (A, B, C, D)
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