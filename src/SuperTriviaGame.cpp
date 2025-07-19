#include "SuperTriviaGame.h"
#include "SpriteDisplay.h"
#include <iostream>
#include <cctype>
#include <limits>

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
    extraLifeActive(false), revealHintActive(false), 
    nextQuestionDoublePoints(false), nextQuestionReducedOptions(false), 
    nextQuestionRevealHint(false), rewardLevel(0)
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
    nextQuestionDoublePoints = false;
    nextQuestionReducedOptions = false;
    nextQuestionRevealHint = false;
}

void SuperTriviaGame::applyPowerUpEffect() {
    switch (powerUp.getType()) {
        case DOUBLE_POINTS: nextQuestionDoublePoints = true; break;
        case REDUCED_OPTIONS: nextQuestionReducedOptions = true; break;
        case EXTRA_LIFE: extraLifeActive = true; break; // Este sí dura hasta que se use
        case REVEAL_HINT: nextQuestionRevealHint = true; break;
        default: break;
    }
    powerUp.applyEffect();
}

void SuperTriviaGame::showFinalResults() {
    calculateReward();
    
    // Guardar el puntaje del jugador
    player.setScore(correctAnswers);
    player.saveScore();
    
    // Limpiar pantalla antes de mostrar resultados
    clearConsole();
    
    // Mostrar sprite según resultado
    if (correctAnswers >= requiredToWin) {
        cout << "\n╔══════════════════════════════════════════════════════════════════════════════╗\n";
        cout << "║                              🎉 ¡FELICIDADES! 🎉                            ║\n";
        cout << "╚══════════════════════════════════════════════════════════════════════════════╝\n";
        cout << "DEBUG: Llamando a displayHappySprite()\n";
        displayHappySprite();
        cout << "DEBUG: displayHappySprite() completado\n";
    } else {
        cout << "\n╔══════════════════════════════════════════════════════════════════════════════╗\n";
        cout << "║                              😠 ¡MEJORA TU JUEGO! 😠                        ║\n";
        cout << "╚══════════════════════════════════════════════════════════════════════════════╝\n";
        cout << "DEBUG: Llamando a displayAngrySprite()\n";
        displayAngrySprite();
        cout << "DEBUG: displayAngrySprite() completado\n";
    }
    
    cout << "\n";
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
        bool validDifficulty = false;
        
        while (!validDifficulty) {
            std::cout << "Enter your choice: ";
            if (!(std::cin >> level)) {
                // Handle invalid input (non-char)
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "\n❌ Invalid input. Please enter a single letter (F, M, or A).\n";
                std::cout << "Press any key to try again...";
                std::cin.get();
                clearConsole();
                displayDifficultyMenu();
                continue;
            }
            
            level = toupper(level);

            if (level == 'F' || level == 'M' || level == 'A') {
                // Show confirmation with difficulty details
                clearConsole();
                const std::string GREEN = "\033[1;32m";
                const std::string YELLOW = "\033[1;33m";
                const std::string RED = "\033[1;31m";
                const std::string WHITE = "\033[1;37m";
                const std::string RESET = "\033[0m";
                
                std::string difficultyName, difficultyColor;
                if (level == 'F') {
                    difficultyName = "FACIL (EASY)";
                    difficultyColor = GREEN;
                } else if (level == 'M') {
                    difficultyName = "MEDIO (MEDIUM)";
                    difficultyColor = YELLOW;
                } else {
                    difficultyName = "AVANZADO (ADVANCED)";
                    difficultyColor = RED;
                }
                
                std::cout << "\n╔══════════════════════════════════════════════════════════════════════════════╗\n";
                std::cout << "║                              🎯 DIFFICULTY CONFIRMATION 🎯                    ║\n";
                std::cout << "╠══════════════════════════════════════════════════════════════════════════════╣\n";
                std::cout << "║                                                                              ║\n";
                std::cout << "║  You selected: " << difficultyColor << difficultyName << WHITE << "\n";
                std::cout << "║                                                                              ║\n";
                std::cout << "║  Are you sure you want to play with this difficulty? (Y/N):                ║\n";
                std::cout << "║                                                                              ║\n";
                std::cout << "╚══════════════════════════════════════════════════════════════════════════════╝\n";
                std::cout << "\nEnter Y to confirm or N to choose again: ";
                
                char confirm;
                if (!(std::cin >> confirm)) {
                    // Handle invalid input
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input. Please enter Y or N.\n";
                    std::cout << "Press any key to continue...";
                    std::cin.get();
                    clearConsole();
                    displayDifficultyMenu();
                    continue;
                }
                confirm = toupper(confirm);
                
                if (confirm == 'Y') {
                    validDifficulty = true;
                    std::cout << "\n" << difficultyColor << "Perfect! Starting with " << difficultyName << " difficulty..." << RESET << "\n";
                    std::cout << "Press any key to continue...";
                    std::cin.ignore();
                    std::cin.get();
                    
                    // Show rewards information for the selected difficulty
                    clearConsole();
                    displayDifficultyRewards(level);
                    std::cin.ignore();
                    std::cin.get();
                } else if (confirm == 'N') {
                    clearConsole();
                    displayDifficultyMenu();
                    continue;
                } else {
                    std::cout << "Invalid input. Please enter Y or N.\n";
                    std::cout << "Press any key to continue...";
                    std::cin.ignore();
                    std::cin.get();
                    clearConsole();
                    displayDifficultyMenu();
                    continue;
                }
            } else {
                std::cout << "\n❌ Invalid input. Please enter F, M, or A.\n";
                std::cout << "Press any key to try again...";
                std::cin.ignore();
                std::cin.get();
                clearConsole();
                displayDifficultyMenu();
            }
        }

        auto questions = questionManager.getRandomQuestionsByLevel(level, totalQuestions);

        for (int i = 0; i < totalQuestions; ++i) {
            // Activar powerups temporales para esta pregunta
            if (nextQuestionDoublePoints) {
                doublePointsActive = true;
                nextQuestionDoublePoints = false;
            }
            if (nextQuestionReducedOptions) {
                reducedOptionsActive = true;
                nextQuestionReducedOptions = false;
            }
            if (nextQuestionRevealHint) {
                revealHintActive = true;
                nextQuestionRevealHint = false;
            }
            
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

            // Show question with powerups applied
            clearConsole();
            displayProgressBar(i + 1, totalQuestions);
            
            // Mostrar powerups activos si los hay
            if (reducedOptionsActive || revealHintActive || doublePointsActive) {
                cout << "\n╔══════════════════════════════════════════════════════════════════════════════╗\n";
                cout << "║                              ⚡ POWER-UPS ACTIVOS ⚡                          ║\n";
                cout << "╠══════════════════════════════════════════════════════════════════════════════╣\n";
                if (doublePointsActive) {
                    cout << "║  ⭐ Double Points: Las respuestas correctas dan 2 puntos!                ║\n";
                }
                if (reducedOptionsActive) {
                    cout << "║  🎲 Opciones Reducidas: Solo se muestran 2 opciones por pregunta          ║\n";
                }
                if (revealHintActive) {
                    cout << "║  💡 Pista Revelada: Se muestra una pista para cada pregunta              ║\n";
                }
                cout << "╚══════════════════════════════════════════════════════════════════════════════╝\n";
            }
            
            // Usar el método display de Question que maneja los powerups
            questions[i].display(reducedOptionsActive, revealHintActive);

            char answer;
            bool validAnswer = false;
            while (!validAnswer) {
                cin >> answer;
                answer = toupper(answer);
                
                // Validate that the answer is a valid option based on active powerups
                if (reducedOptionsActive) {
                    // With reduced options, only A and B are valid
                    if (answer == 'A' || answer == 'B') {
                        validAnswer = true;
                    } else {
                        cout << "Invalid option. Please enter A or B.\n";
                    }
                } else {
                    // Normal validation (A, B, C, D)
                    if (answer == 'A' || answer == 'B' || answer == 'C' || answer == 'D') {
                        validAnswer = true;
                    } else {
                        cout << "Invalid option. Please enter A, B, C, or D.\n";
                    }
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
                        
                        // Validate that the answer is a valid option based on active powerups
                        if (reducedOptionsActive) {
                            // With reduced options, only A and B are valid
                            if (answer == 'A' || answer == 'B') {
                                validAnswer = true;
                            } else {
                                cout << "Invalid option. Please enter A or B.\n";
                            }
                        } else {
                            // Normal validation (A, B, C, D)
                            if (answer == 'A' || answer == 'B' || answer == 'C' || answer == 'D') {
                                validAnswer = true;
                            } else {
                                cout << "Invalid option. Please enter A, B, C, or D.\n";
                            }
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

            // Desactivar powerups que solo duran una pregunta
            doublePointsActive = false;
            reducedOptionsActive = false;
            revealHintActive = false;
            // NO desactivar extraLifeActive aquí ya que debe durar hasta que se use
        }

        showFinalResults();
        resetPowerUps(); // Reset all powerups at the end of the game
        askPlayAgain(playAgain);
    }

    cout << "\nThanks for playing! Goodbye!\n";
}