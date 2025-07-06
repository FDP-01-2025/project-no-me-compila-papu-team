#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
private:
    std::string firstName;
    std::string lastName;
    int score;

public:
    Player();

    void inputPlayerInfo();               // Pide nombre y apellido
    std::string getFullName() const;      // Devuelve "Nombre Apellido"
    void setScore(int newScore);          // Asigna puntaje
    int getScore() const;                 // Devuelve puntaje
    void saveScore();                     // Guarda o actualiza archivo
};

#endif