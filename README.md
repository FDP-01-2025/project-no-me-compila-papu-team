### Game Title
Who Wants to Stop Being Poor?

### Theme and Setting
The game is presented as an educational quiz show, blending learning and entertainment. Players are immersed in a dynamic environment where they must answer trivia questions related to mathematics and computer science. With humor and a gamified structure, the game promotes cognitive engagement while simulating a game-show-like experience.

## Core Mechanics
The main mechanic is a multiple-choice trivia system. Players are presented with 10 randomly selected questions from a large database categorized by difficulty:
- Easy, Medium, and Hard, each with 35 curated questions.
- Each question has four possible answers (A, B, C, D), and the player must select the correct one.
- Every 3 questions, a random mini-game (Tic-Tac-Toe, Rock-Paper-Scissors, or Hangman) is triggered.

If the player wins the mini-game, they receive a Power-Up (e.g., Double Points, Reduced Options, Extra Life, or Reveal Hint), which enhances their performance in the remaining trivia questions.
After the 10th question, the game evaluates the player's score:
- If the player answers at least 5 questions correctly, a happy ASCII sprite is shown.
- Otherwise, an angry sprite appears.
The player's full name and final score are displayed, and the game asks whether they wish to play again.

### Gameplay Overview
1. The player enters their first and last name.
2. The game prompts for a difficulty level (F/M/A).
3. 10 questions are shown, randomly selected from the chosen difficulty pool.
4. Every 3 questions, the player plays a mini-game.
5. Based on mini-game performance, a Power-Up may be granted.
6. The game displays the final score, sprite feedback, and replay prompt.

### Application of Course Topics
**Variables and Data Types**
Variables and appropriate data types are fundamental to managing player information, game state, and configuration across all components of the game.
They are used to store:
- Player input (e.g., name, selected difficulty)
- Current scores and counters
- Player answers and system feedback
- Power-Up activation flags
- Internal state for mini-games

Example:
string firstName, lastName;    // Player identification
char selectedOption;           // Player's chosen answer (A, B, C, D)
int score = 0;                 // Tracks correct answers
bool powerUpActive = false;    // Indicates if a Power-Up is applied

Data types are chosen based on the nature of the data — string for text, char for options, int for numerical values, and bool for logical states.

**Conditional Structures (if, else, switch)**
Conditional statements are used extensively to control game logic and respond dynamically to user actions. They determine what happens based on:
- Whether a player answered correctly
- Power-Up activation and effects
- Mini-game outcomes
- Game progression (e.g., end of round, retry prompts)

Example1:
if (playerScore > computerScore) {
    cout << "\nYou win the mini-game!\n";
    return true;
} else if (computerScore > playerScore) {
    cout << "\nComputer wins the mini-game!\n";
    return false;
} else {
    cout << "\nIt's a tie in the mini-game!\n";
    return false;
}

Example2:
switch (powerUp.getType()) {
    case DOUBLE_POINTS: doublePointsActive = true; break;
    case REDUCED_OPTIONS: reducedOptionsActive = true; break;
    case EXTRA_LIFE: extraLifeActive = true; break;
    case REVEAL_HINT: revealHintActive = true; break;
    default: break;
}

**Loops (for, while, do-while)**
Loops are used extensively to manage the game's flow, enhance user interaction, and ensure robustness in input handling.
They are applied in:
- Question iteration: Presenting each trivia question one by one.
- Input validation: Re-prompting users for valid answers or levels.
- Mini-game rounds: Repeating actions in games like Rock-Paper-Scissors (best of 3).
- Searching and filtering: Looping through collections to locate data (e.g., computer's AI in Tic-Tac-Toe).

Example:
for (int i = 0; i < 9; i++) {
    if (board[i] == ' ') {
        board[i] = computerMark;
        if (isWinner(computerMark)) {
            board[i] = ' '; // Undo move after checking
            return i;
        }
        board[i] = ' ';
    }
}
This for loop scans the board and simulates placing the computer's mark (O) in empty positions to check if any move leads to a win. If a winning move is found, that index is returned.

**Functions**
All core components of the game are implemented using modular functions and class methods, ensuring clean separation of logic and easy maintenance.
Functions are used for:
- Displaying questions and handling answers.
- Running mini-games.
- Managing power-ups and score logic.
- Drawing game boards and ASCII feedback.
- Handling user input and validating data.

Example:
bool playTicTacToe() {
    TicTacToe game;
    return game.play(); // Returns true only if the player wins
}
This function encapsulates the execution of the Tic-Tac-Toe mini-game and returns a boolean result based on the outcome. The return value is later used to determine whether to grant the player a power-up in the main trivia game.

**Data Structures**
The project utilizes several core data structures to manage the trivia system efficiently. These include:
- Classes: Used to encapsulate logic and data (e.g., Question, QuestionManager).
- Vectors: Used to dynamically store and manipulate collections of questions and answer options.

vector<Question> QuestionManager::getRandomQuestionsByLevel(char levelCode, int count) {
    vector<Question> filtered;  // ← dynamic list of filtered questions

    for (const auto& q : allQuestions) {
        if (toupper(q.level[0]) == toupper(levelCode)) {
            filtered.push_back(q); // ← add to vector if level matches
        }
    }

    shuffle(filtered.begin(), filtered.end(), default_random_engine(time(0)));

    if (filtered.size() > count)
        filtered.resize(count); // ← ensure only 'count' questions are returned

    return filtered;
}

* Explanation:
- The vector<Question> structure is used here to store and manage a dynamic list of questions filtered by difficulty level.
- The Question class encapsulates each question's data: text, answer options, correct answer, and level.
- The allQuestions vector holds all loaded questions, populated from a file in the loadFromFile() method.
- filtered is filled based on the level selected by the user (F, M, or A), allowing flexible retrieval.
- The shuffle() and resize() functions operate directly on the vector to provide a random selection of fixed size.

* Class and Struct Design
class QuestionManager {
private:
    std::vector<Question> allQuestions;

public:
    bool loadFromFile(const std::string& filename);
    std::vector<Question> getRandomQuestionsByLevel(char levelCode, int count);
};

* Explanation:
- QuestionManager encapsulates the storage and handling of all trivia questions.
- It loads data from a text file and filters questions based on the selected difficulty level.
- The use of private attributes and public methods follows standard class design practices that promote encapsulation.
This structure promotes modularity, encapsulation, and separation of concerns, making the code easier to scale and maintain.

**File Handling**
To ensure scalability and flexibility, the game reads all trivia questions from a plain text file (trivia_data.txt). This allows easy updates and additions without modifying the source code.

File Structure
Each line in the file represents one question, using the following format:
Level|Question|Option1|Option2|Option3|Option4|CorrectLetter

Example:
F|What is the output of 2 + 2 in C++?|2|3|4|5|C
M|Which data structure uses FIFO?|Stack|Queue|Tree|Graph|B

- Implementation Example
bool QuestionManager::loadFromFile(const string& filename) {
    ifstream file(filename);  // Open the file
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

        allQuestions.push_back(ques);  // Add to in-memory vector
    }

    return true;
}

* Explanation
- The game opens the file using ifstream.
- Each line is read and split using getline and the | separator.
- A Question object is created with the parsed data and added to a vector (allQuestions), which stores all questions for the game session.

**Error Handling**
Robust error handling mechanisms were implemented throughout the project to improve the user experience and prevent unexpected behavior. These checks handle invalid inputs, file access issues, and gameplay flow interruptions.

* File Access Validation
The game verifies if the trivia file (trivia_data.txt) exists and is accessible before attempting to load questions. If the file fails to open, an error message is shown and the game cannot proceed.

Example:
if (!questionManager.loadFromFile("trivia_data.txt")) {
    cout << "Error loading trivia questions file!\n";
}

**Console Interface**
All user interaction is handled through the command line interface, using formatted text, clear prompts, and ASCII-based visuals to enhance the player experience.

This includes:
- ASCII sprites for feedback at the end of each round (e.g., a happy or angry face depending on the player's performance).
- Board rendering for mini-games like Tic-Tac-Toe, making the game visually intuitive even in a text-based environment.

Example:
void drawBoard() {
    cout << endl;
    cout << " " << board[0] << " | " << board[1] << " | " << board[2] << endl;
    cout << "---+---+---" << endl;
    cout << " " << board[3] << " | " << board[4] << " | " << board[5] << endl;
    cout << "---+---+---" << endl;
    cout << " " << board[6] << " | " << board[7] << " | " << board[8] << endl << endl;
}
This function displays the current state of the Tic-Tac-Toe board using formatted console output, helping the player visualize the game state effectively.

### Technical Development Considerations
- Language: C++ (C++11 standard)
- Organization: Modular design using .cpp and .h files per component (e.g., Question.h, MiniGameHandler.h)
- Cross-platform: Compatible with Linux, Windows, and macOS (with terminal support)
- Randomization: Uses rand() and shuffle() for fair gameplay
- Power-Up System: Dynamic effects applied mid-round
- ASCII Graphics: Lightweight, no additional libraries needed

### Mockups


### Execution Instructions
Follow the steps below to compile and run the game “Who Wants to Stop Being Poor?” on your machine.
 **Requirements**
- A C++ compiler (g++ recommended).
- A terminal or command-line interface.
- The project source files should be located inside a src/ folder.
- The main file (main.cpp) should be in the root or specified location.
- The file preguntas.txt containing the trivia questions must be available and correctly formatted.

**Compilation**
To compile the entire game, use the following command in your terminal from the root directory of the project:
bash
g++ -Isrc main.cpp -o test

**Explanation:**
- -Isrc: Tells the compiler to look for header files in the src/ folder.
- main.cpp: The entry point of the game.
- -o test: Specifies the name of the output executable (test).
Make sure all .cpp and .h files in src/ are correctly included or referenced from main.cpp.

**Running the Game**
After compilation, run the game with:
bash
./test

On Windows:
bash
test.exe

### Team
**Team Name:** No me compila papu team 

### Team Members
1. **Full Name:** Alejandra Paola Orellana Valladares
    **ID:** 00108225

2. **Full Name:** Edgar Ari Peñate Rivera
    **ID:** 00021725

3. **Full Name:** Josué Gabriel Sánchez González
    **ID:** 00159925

4. **Full Name:** Víctor José Tamayo Hernández
    **ID:** 00087025