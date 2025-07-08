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
        for (int i : indices) {
            reducedOptions.push_back(options[i]);
        }
        displayOptions = reducedOptions;
    }

    if (showHint) {
        // Add hint to the question
        string questionWithHint = question + "\n💡 Hint: The correct answer is option " + correctAnswer;
        displayQuestionBox(questionWithHint, displayOptions, 0, 0, 0); // Parameters will be passed from SuperTriviaGame
    } else {
        displayQuestionBox(question, displayOptions, 0, 0, 0); // Parameters will be passed from SuperTriviaGame
    }
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