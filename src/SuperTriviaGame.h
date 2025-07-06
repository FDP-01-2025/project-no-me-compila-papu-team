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

    // Control de power-ups durante la ronda
    bool doublePointsActive;
    bool reducedOptionsActive;
    bool extraLifeActive;
    bool revealHintActive;

    void resetPowerUps();
    void applyPowerUpEffect();
    void showFinalResults();
    void askPlayAgain(bool &playAgain);

public:
    SuperTriviaGame();
    void start();
};

#endif