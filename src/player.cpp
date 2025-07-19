#include "Player.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;

Player::Player() : score(0) {}

void Player::inputPlayerInfo() {
    displayPlayerRegistration();
    cout << "│  Name: ";
    getline(cin >> ws, firstName);
    cout << "│  Last Name: ";
    getline(cin >> ws, lastName);
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

    // Read existing players
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

    // Update or add new player
    players[getFullName()] = score;

    // Save all again
    ofstream outfile("data/player_scores.txt");
    for (const auto& p : players) {
        outfile << p.first << "|" << p.second << "\n";
    }
    outfile.close();
}

void Player::displaySavedScores() {
    cout << "\n╔══════════════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                              🏆 HIGH SCORES 🏆                              ║\n";
    cout << "╠══════════════════════════════════════════════════════════════════════════════╣\n";
    cout << "║                                                                              ║\n";
    
    ifstream infile("data/player_scores.txt");
    if (!infile.is_open()) {
        cout << "║  ❌ No saved scores found.                                                ║\n";
        cout << "║                                                                              ║\n";
        cout << "╚══════════════════════════════════════════════════════════════════════════════╝\n";
        cout << "\nPress any key to continue...";
        cin.ignore();
        cin.get();
        return;
    }
    
    string line;
    bool hasScores = false;
    int lineCount = 0;
    
    // Leer todas las líneas primero para contar
    vector<pair<string, int>> scores;
    while (getline(infile, line)) {
        stringstream ss(line);
        string name;
        int score;
        if (getline(ss, name, '|') && ss >> score) {
            scores.push_back({name, score});
            hasScores = true;
        }
    }
    infile.close();
    
    if (!hasScores) {
        cout << "║  ❌ No saved scores found.                                                ║\n";
    } else {
        // Ordenar por puntaje (mayor a menor)
        sort(scores.begin(), scores.end(), 
             [](const pair<string, int>& a, const pair<string, int>& b) {
                 return a.second > b.second;
             });
        
        // Mostrar los mejores 10 puntajes
        int maxDisplay = min(10, (int)scores.size());
        for (int i = 0; i < maxDisplay; i++) {
            string rank = to_string(i + 1);
            if (i == 0) rank = "🥇";
            else if (i == 1) rank = "🥈";
            else if (i == 2) rank = "🥉";
            
            cout << "║  " << rank << " " << scores[i].first;
            // Rellenar espacios para alinear
            int spaces = 50 - scores[i].first.length();
            for (int j = 0; j < spaces; j++) cout << " ";
            cout << " " << scores[i].second << " pts ║\n";
        }
    }
    
    cout << "║                                                                              ║\n";
    cout << "╚══════════════════════════════════════════════════════════════════════════════╝\n";
    cout << "\nPress any key to continue...";
    cin.ignore();
    cin.get();
}