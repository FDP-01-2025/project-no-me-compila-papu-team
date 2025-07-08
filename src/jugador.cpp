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
    ifstream infile("data/player_scores.txt");
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
    ofstream outfile("data/player_scores.txt");
    for (const auto& p : players) {
        outfile << p.first << "|" << p.second << "\n";
    }
    outfile.close();
}

void Player::displaySavedScores() {
    cout << "\n=== SAVED SCORES ===\n";
    cout << "Name\t\t\tScore\n";
    cout << "------------------------\n";
    
    ifstream infile("data/player_scores.txt");
    if (!infile.is_open()) {
        cout << "No saved scores found.\n";
        return;
    }
    
    string line;
    bool hasScores = false;
    while (getline(infile, line)) {
        stringstream ss(line);
        string name;
        int score;
        if (getline(ss, name, '|') && ss >> score) {
            cout << name << "\t\t" << score << "\n";
            hasScores = true;
        }
    }
    infile.close();
    
    if (!hasScores) {
        cout << "No saved scores found.\n";
    }
    
    cout << "\nPress any key to continue...";
    cin.ignore();
    cin.get();
}