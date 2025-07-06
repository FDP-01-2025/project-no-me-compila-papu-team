#!/bin/bash

# Script para compilar el proyecto con g++ main.cpp -o test
# Este script combina todos los archivos .cpp en un solo comando

cd src

# Compilar todos los archivos .cpp en un solo comando
g++ -std=c++11 -Wall -o ../test main.cpp SuperTriviaGame.cpp jugador.cpp preguntas.cpp potenciadores.cpp sprite.cpp trivia.cpp Crossword.cpp Hangman.cpp RPSGame.cpp TicTacToe.cpp MiniGameHandler.cpp

echo "Compilación completada. Ejecuta './test' para correr el programa." 