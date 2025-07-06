#include "TriviaGame.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

struct Question {
    string level;
    string question;
    string options[4];
    char correct;
};

class TriviaEngine {
private:
    vector<Question> questions;

    void loadQuestions() {
        ifstream file("trivia_data.txt");
        string line;
        while (getline(file, line)) {
            Question q;
            size_t pos = 0;
            vector<string> tokens;
            while ((pos = line.find('|')) != string::npos) {
                tokens.push_back(line.substr(0, pos));
                line.erase(0, pos + 1);
            }
            tokens.push_back(line); // last part (correct answer)

            if (tokens.size() == 7) {
                q.level = tokens[0];
                q.question = tokens[1];
                for (int i = 0; i < 4; ++i)
                    q.options[i] = tokens[2 + i];
                q.correct = tokens[6][0];
                questions.push_back(q);
            }
        }
    }

    vector<Question> getQuestionsByLevel(char levelChar) {
        vector<Question> selected;
        for (const auto& q : questions) {
            if (q.level[0] == levelChar)
                selected.push_back(q);
        }
        return selected;
    }

    void askQuestions(const vector<Question>& pool) {
        vector<Question> gameQuestions = pool;
        random_shuffle(gameQuestions.begin(), gameQuestions.end());
        if (gameQuestions.size() > 10)
            gameQuestions.resize(10);

        int score = 0;

        for (size_t i = 0; i < gameQuestions.size(); ++i) {
            const Question& q = gameQuestions[i];
            cout << "\nQuestion " << i + 1 << ":\n";
            cout << q.question << "\n";
            cout << "A) " << q.options[0] << "\n";
            cout << "B) " << q.options[1] << "\n";
            cout << "C) " << q.options[2] << "\n";
            cout << "D) " << q.options[3] << "\n";

            char answer;
            cout << "Your answer (A/B/C/D): ";
            cin >> answer;
            answer = toupper(answer);

            if (answer == q.correct) {
                cout << " Correct!\n";
                score++;
            } else {
                cout << " Incorrect. Correct answer: " << q.correct << ")\n";
            }
        }

        cout << "\n Final Score: " << score << "/10\n";
    }

public:
    TriviaEngine() {
        srand(time(0));
        loadQuestions();
    }

    void run() {
        cout << " Welcome to the Trivia Challenge!\n";
        cout << "Choose difficulty level:\n";
        cout << "F - Easy\nM - Medium\nA - Hard\n";
        char level;
        while (true) {
            cout << "Your choice: ";
            cin >> level;
            level = toupper(level);
            if (level == 'F' || level == 'M' || level == 'A')
                break;
            cout << "Invalid option. Try F, M, or A.\n";
        }

        vector<Question> selected = getQuestionsByLevel(level);
        if (selected.size() < 10) {
            cout << " Not enough questions for this level.\n";
            return;
        }

        askQuestions(selected);
    }
};

// Interfaz pública
TriviaGame::TriviaGame() {}
void TriviaGame::play() {
    TriviaEngine engine;
    engine.run();
}