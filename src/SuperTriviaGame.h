#ifndef SUPERTRIVIAGAME_H
#define SUPERTRIVIAGAME_H

#include "Player.h"
#include "PowerUp.h"
#include "Question.h"
#include "SpriteDisplay.h"
#include "MiniGameHandler.h"

class SuperTriviaGame {
private:
    Player player;
    PowerUp powerUp;
    MiniGameHandler miniGameHandler;
    QuestionManager questionManager;

    int correctAnswers;
    int totalQuestions;
    int requiredToWin;  // Minimum correct answers to win

    // Control de power-ups durante la ronda
    bool doublePointsActive;
    bool reducedOptionsActive;
    bool extraLifeActive;
    bool revealHintActive;
    
    // Powerups temporales (solo para la siguiente pregunta)
    bool nextQuestionDoublePoints;
    bool nextQuestionReducedOptions;
    bool nextQuestionRevealHint;

    // Reward system
    int rewardLevel;  // 0: No reward, 1: Small chocolate, 2: 2 small chocolates, 3: Chocolate bar

    void resetPowerUps();
    void applyPowerUpEffect();
    void showFinalResults();
    void askPlayAgain(bool &playAgain);
    void calculateReward();
    void offerRevengeGame();

public:
    SuperTriviaGame();
    void start();
};

#endif