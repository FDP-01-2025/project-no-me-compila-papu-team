#ifndef QUESTION_H
#define QUESTION_H

#include <string>
#include <vector>

struct Question {
    std::string level;     // "F", "M", "A"
    std::string question;
    std::vector<std::string> options;  // A, B, C, D
    char correctAnswer;

    Question() = default;
    void display(bool reducedOptions = false, bool showHint = false) const;
    bool checkAnswer(char answer) const;
};

class QuestionManager {
private:
    std::vector<Question> allQuestions;

public:
    bool loadFromFile(const std::string& filename);
    std::vector<Question> getRandomQuestionsByLevel(char levelCode, int count);
};

#endif