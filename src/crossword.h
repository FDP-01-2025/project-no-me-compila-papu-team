#ifndef CROSSWORD_H
#define CROSSWORD_H

#include <string>
#include <vector>

class Crossword {
private:
    static const int SIZE = 12;
    char board[SIZE][SIZE];
    std::vector<std::string> wordList;
    std::vector<std::string> foundWords;
    std::string playerName;

    void initializeBoard();
    void loadWordsFromFile(const std::string& filename);
    void placeWords();
    void fillEmptySpaces();
    void drawBoard();
    bool checkWord(const std::string& input);
    void saveScoreToFile(int score);
public:
    Crossword();
    void startGame();
};

#endif
