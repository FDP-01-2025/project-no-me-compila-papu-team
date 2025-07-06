#include "Player.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

Player::Player() : score(0) {}

void Player::inputPlayerInfo() {
    cout << "Enter your first name: ";
    cin >> firstName;
    cout << "Enter your last name: ";
    cin >> lastName;
}

string Player::getFullName() const {
    return firstName + " " + lastName;
}

void Player::setScore(int newScore) {
    score = newScore;
}

int Player::getScore() const {
    return score;
}

void Player::saveScore() {
    map<string, int> players;

    // Leer jugadores existentes
    ifstream infile("player_scores.txt");
    string line;
    while (getline(infile, line)) {
        stringstream ss(line);
        string name;
        int sc;
        if (getline(ss, name, '|') && ss >> sc) {
            players[name] = sc;
        }
    }
    infile.close();

    // Actualizar o añadir nuevo jugador
    players[getFullName()] = score;

    // Guardar todos de nuevo
    ofstream outfile("player_scores.txt");
    for (const auto& p : players) {
        outfile << p.first << "|" << p.second << "\n";
    }
    outfile.close();
}