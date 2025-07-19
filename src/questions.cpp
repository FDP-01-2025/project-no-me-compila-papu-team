#include "Question.h"
#include "SpriteDisplay.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <random>
#include <ctime>
#include <vector>

using namespace std;

void Question::display(bool reducedOptions, bool showHint) const {
    // Use the new improved interface
    vector<string> displayOptions = options;
    vector<char> displayLetters = {'A', 'B', 'C', 'D'};
    
    if (reducedOptions) {
        // Always include correct answer, plus one random incorrect
        vector<int> indices;
        indices.push_back(correctAnswer - 'A');

        vector<int> wrong;
        for (int i = 0; i < 4; ++i)
            if (i != (correctAnswer - 'A')) wrong.push_back(i);
        indices.push_back(wrong[rand() % wrong.size()]);
        shuffle(indices.begin(), indices.end(), default_random_engine(rand()));
        
        // Create reduced options
        vector<string> reducedOptions;
        vector<char> reducedLetters;
        for (int i = 0; i < indices.size(); i++) {
            reducedOptions.push_back(options[indices[i]]);
            reducedLetters.push_back('A' + i);
        }
        displayOptions = reducedOptions;
        displayLetters = reducedLetters;
    }

    // Show question with new interface
    cout << "\n╔══════════════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                              🧠 PREGUNTA 🧠                                    ║\n";
    cout << "╠══════════════════════════════════════════════════════════════════════════════╣\n";
    cout << "║                                                                              ║\n";
    
    // Show question with formatted output
    string questionText = question;
    if (showHint) {
        if (reducedOptions) {
            // Con opciones reducidas, mostrar la respuesta correcta directamente
            questionText += "\n💡 Hint: The correct answer is: " + getCorrectAnswer();
        } else {
            // Con todas las opciones, mostrar la letra
            questionText += "\n💡 Hint: The correct answer is option " + string(1, correctAnswer);
        }
    }
    cout << "║  " << questionText << "\n";
    cout << "║                                                                              ║\n";
    
    // Show options with improved formatting
    for (int j = 0; j < displayOptions.size(); j++) {
        cout << "║  🎯 " << displayLetters[j] << ") " << displayOptions[j];
        // Fill spaces to keep alignment
        int spaces = 70 - displayOptions[j].length();
        for (int k = 0; k < spaces; k++) cout << " ";
        cout << " ║\n";
    }
    
    cout << "║                                                                              ║\n";
    cout << "╚══════════════════════════════════════════════════════════════════════════════╝\n";
    cout << "\n🎯 Tu respuesta (";
    for (int j = 0; j < displayLetters.size(); j++) {
        cout << displayLetters[j];
        if (j < displayLetters.size() - 1) cout << "/";
    }
    cout << "): ";
}

bool Question::checkAnswer(char answer) const {
    return toupper(answer) == correctAnswer;
}

std::string Question::getCorrectAnswer() const {
    return options[correctAnswer - 'A'];
}

bool QuestionManager::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) return false;

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string level, q, a, b, c, d, correct;
        getline(ss, level, '|');
        getline(ss, q, '|');
        getline(ss, a, '|');
        getline(ss, b, '|');
        getline(ss, c, '|');
        getline(ss, d, '|');
        getline(ss, correct, '|');

        Question ques;
        ques.level = level;
        ques.question = q;
        ques.options = {a, b, c, d};
        ques.correctAnswer = correct[0];

        allQuestions.push_back(ques);
    }

    return true;
}

vector<Question> QuestionManager::getRandomQuestionsByLevel(char levelCode, int count) {
    vector<Question> filtered;
    for (const auto& q : allQuestions) {
        if (toupper(q.level[0]) == toupper(levelCode)) {
            filtered.push_back(q);
        }
    }

    shuffle(filtered.begin(), filtered.end(), default_random_engine(time(0)));

    if (filtered.size() > count)
        filtered.resize(count);

    return filtered;
}