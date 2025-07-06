// This file contains all implementations in the correct order
// to avoid redefinition conflicts

// First include all headers
#include "Player.h"
#include "PowerUp.h"
#include "Question.h"
#include "SpriteDisplay.h"
#include "MiniGameHandler.h"
#include "SuperTriviaGame.h"

// Then include implementations in dependency order
#include "jugador.cpp"
#include "preguntas.cpp"
#include "potenciadores.cpp"
#include "sprite.cpp"
#include "Crossword.cpp"
#include "Hangman.cpp"
#include "RPSGame.cpp"
#include "TicTacToe.cpp"
#include "MiniGameHandler.cpp"
#include "SuperTriviaGame.cpp" 