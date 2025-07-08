#include "SpriteDisplay.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <regex>

using namespace std;

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Función auxiliar para calcular el ancho visual de una cadena ignorando ANSI y contando emojis como doble
int visualLength(const std::string& s) {
    std::string no_ansi = std::regex_replace(s, std::regex("\\033\\[[0-9;]*m"), "");
    int len = 0;
    for (size_t i = 0; i < no_ansi.size(); ) {
        unsigned char c = no_ansi[i];
        // Emoji unicode (asumimos UTF-8, 4 bytes)
        if ((c & 0xF8) == 0xF0) {
            len += 2; // emoji cuenta como 2
            i += 4;
        } else {
            len++;
            i++;
        }
    }
    return len;
}

// Imprime una línea con padding y bordes
void printColoredLine(const std::string& content, int width = 100) {
    std::cout << "│";
    int vlen = visualLength(content);
    std::cout << content;
    for (int i = 0; i < width - vlen; ++i) std::cout << " ";
    std::cout << "│\n";
}

// Imprime una línea centrada visualmente, solo con borde izquierdo
void printCenteredNoRightBorder(const std::string& content, int width = 100) {
    int vlen = visualLength(content);
    int left = (width - vlen) / 2;
    std::cout << "│";
    for (int i = 0; i < left; ++i) std::cout << " ";
    std::cout << content << "\n";
}

// Imprime una caja de sección con título y líneas
void printSectionBox(const std::vector<std::string>& lines, int width = 100) {
    std::cout << "┌"; for (int i = 0; i < width-2; ++i) std::cout << "─"; std::cout << "┐\n";
    for (const auto& l : lines) printCenteredNoRightBorder(l, width);
    std::cout << "└"; for (int i = 0; i < width-2; ++i) std::cout << "─"; std::cout << "┘\n";
}

void displayWelcomeMessage() {
    clearScreen();
    // Paleta sobria
    const std::string BLUE = "\033[1;34m";
    const std::string CYAN = "\033[0;36m";
    const std::string WHITE = "\033[1;37m";
    const std::string GRAY = "\033[0;37m";
    const std::string RESET = "\033[0m";
    const int WIDTH = 100;

    std::cout << WHITE;
    std::cout << "┌"; for (int i = 0; i < WIDTH-2; ++i) std::cout << "─"; std::cout << "┐\n";
    printCenteredNoRightBorder(BLUE + "🎮 QUIEN QUIERE DEJAR DE SER POBRE? 🎯" + WHITE, WIDTH);
    printCenteredNoRightBorder(CYAN + "Game Collection" + WHITE, WIDTH);
    std::cout << "├"; for (int i = 0; i < WIDTH-2; ++i) std::cout << "─"; std::cout << "┤\n";
    printCenteredNoRightBorder(GRAY + "🎉 ¡Bienvenido a nuestra emocionante colección de juegos! 🎉" + WHITE, WIDTH);
    printCenteredNoRightBorder(GRAY + "🎯 ¡Juega, gana puntos y deja de ser pobre en conocimiento! 🎯" + WHITE, WIDTH);
    std::cout << "├"; for (int i = 0; i < WIDTH-2; ++i) std::cout << "─"; std::cout << "┤\n";
    printCenteredNoRightBorder(CYAN + "🧠 Trivia Challenge: Pon a prueba tus habilidades en Ciencia y Tech" + WHITE, WIDTH);
    printCenteredNoRightBorder(CYAN + "🎲 Mini-Games: Piedra-Papel-Tijeras, TicTacToe, Hangman..." + WHITE, WIDTH);
    printCenteredNoRightBorder(CYAN + "⚡ Power-Ups: ¡Gana mini-juegos y obtén ventajas!" + WHITE, WIDTH);
    printCenteredNoRightBorder(CYAN + "🏆 Sistema de Puntuación: ¡Compite por el mejor score!" + WHITE, WIDTH);
    std::cout << "└"; for (int i = 0; i < WIDTH-2; ++i) std::cout << "─"; std::cout << "┘\n";
    printCenteredNoRightBorder(BLUE + "🎮 Presiona cualquier tecla para comenzar... 🎮" + WHITE, WIDTH);
    std::cout << RESET;
}

void displayMainMenu() {
    const std::string BLUE = "\033[1;34m";
    const std::string CYAN = "\033[0;36m";
    const std::string WHITE = "\033[1;37m";
    const std::string RESET = "\033[0m";
    const int WIDTH = 100;
    clearScreen();
    std::vector<std::string> lines = {
        BLUE + "MENÚ PRINCIPAL" + WHITE,
        CYAN + "1. 🎮 Jugar - ¡Comienza tu viaje para dejar de ser pobre!" + WHITE,
        CYAN + "2. 📊 Ver Puntuaciones - Revisa tu progreso" + WHITE,
        CYAN + "3. 🚪 Salir - Abandona el juego" + WHITE
    };
    printSectionBox(lines, WIDTH);
    printCenteredNoRightBorder(BLUE + "Selecciona una opción (1-3):" + WHITE, WIDTH);
    std::cout << RESET;
}

void displayDifficultyMenu() {
    const std::string CYAN = "\033[0;36m";
    const std::string WHITE = "\033[1;37m";
    const std::string RESET = "\033[0m";
    const int WIDTH = 100;
    std::vector<std::string> lines = {
        CYAN + "Selecciona la dificultad:" + WHITE,
        CYAN + "F - 🟢 Fácil   M - 🟡 Medio   A - 🔴 Avanzado" + WHITE
    };
    printSectionBox(lines, WIDTH);
    printCenteredNoRightBorder(CYAN + "Elige F, M o A:" + WHITE, WIDTH);
    std::cout << RESET;
}

void displayProgressBar(int current, int total, int barWidth) {
    float progress = (float)current / total;
    int pos = barWidth * progress;
    
    cout << "\n╔══════════════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                              📊 PROGRESO DEL JUEGO 📊                        ║\n";
    cout << "╠══════════════════════════════════════════════════════════════════════════════╣\n";
    cout << "║  Pregunta " << current << " de " << total << " ";
    
    // Centrar la barra de progreso
    int spaces = 50 - barWidth;
    for (int i = 0; i < spaces/2; i++) cout << " ";
    
    cout << "[";
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) cout << "█";
        else if (i == pos) cout << "▶";
        else cout << "░";
    }
    cout << "] " << int(progress * 100.0) << "%\n";
    cout << "╚══════════════════════════════════════════════════════════════════════════════╝\n";
}

void displayQuestionBox(const string& question, const vector<string>& options, int questionNumber, int totalQuestions, int score) {
    clearScreen();
    displayProgressBar(questionNumber, totalQuestions);
    
    cout << "\n╔══════════════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                              🧠 PREGUNTA " << questionNumber << "/" << totalQuestions << " 🧠                          ║\n";
    cout << "║                              📊 Puntuación: " << score << " puntos 📊                        ║\n";
    cout << "╠══════════════════════════════════════════════════════════════════════════════╣\n";
    cout << "║                                                                              ║\n";
    
    // Mostrar pregunta con formato
    cout << "║  " << question << "\n";
    cout << "║                                                                              ║\n";
    
    // Mostrar opciones con formato mejorado
    char optionLetters[] = {'A', 'B', 'C', 'D'};
    for (int i = 0; i < options.size(); i++) {
        cout << "║  🎯 " << optionLetters[i] << ") " << options[i];
        // Rellenar espacios para mantener alineación
        int spaces = 70 - options[i].length();
        for (int j = 0; j < spaces; j++) cout << " ";
        cout << " ║\n";
    }
    
    cout << "║                                                                              ║\n";
    cout << "╚══════════════════════════════════════════════════════════════════════════════╝\n";
    cout << "\n🎯 Tu respuesta (A/B/C/D): ";
}

void displayCorrectAnswer() {
    const std::string GREEN = "\033[1;32m";
    const std::string WHITE = "\033[1;37m";
    const std::string RESET = "\033[0m";
    const int WIDTH = 100;
    std::vector<std::string> lines = {
        GREEN + "✅ ¡CORRECTO!" + WHITE,
        GREEN + "¡Suma un punto a tu marcador!" + WHITE
    };
    printSectionBox(lines, WIDTH);
    std::cout << RESET;
}

void displayIncorrectAnswer(const std::string& correctAnswer) {
    const std::string RED = "\033[1;31m";
    const std::string WHITE = "\033[1;37m";
    const std::string RESET = "\033[0m";
    const int WIDTH = 100;
    std::vector<std::string> lines = {
        RED + "❌ INCORRECTO" + WHITE,
        RED + "La respuesta correcta era: " + correctAnswer + WHITE
    };
    printSectionBox(lines, WIDTH);
    std::cout << RESET;
}

void displayPowerUpMenu() {
    const std::string YELLOW = "\033[1;33m";
    const std::string WHITE = "\033[1;37m";
    const std::string RESET = "\033[0m";
    const int WIDTH = 100;
    std::vector<std::string> lines = {
        YELLOW + "⚡ ¡Elige tu Power-Up!" + WHITE,
        YELLOW + "1. ⭐ Doble Puntos   2. 🎲 Opciones Reducidas   3. 💖 Vida Extra   4. 💡 Revelar Pista" + WHITE
    };
    printSectionBox(lines, WIDTH);
    printCenteredNoRightBorder(YELLOW + "Selecciona 1-4:" + WHITE, WIDTH);
    std::cout << RESET;
}

void displayMiniGameIntro(const std::string& gameName) {
    const std::string CYAN = "\033[0;36m";
    const std::string WHITE = "\033[1;37m";
    const std::string RESET = "\033[0m";
    const int WIDTH = 100;
    std::vector<std::string> lines = {
        CYAN + "🎲 ¡MINI-JUEGO!" + WHITE,
        CYAN + "Juega: " + gameName + WHITE,
        CYAN + "¡Gana para obtener un Power-Up!" + WHITE
    };
    printSectionBox(lines, WIDTH);
    printCenteredNoRightBorder(CYAN + "Presiona cualquier tecla para comenzar..." + WHITE, WIDTH);
    std::cout << RESET;
}

void displayFinalResults(const std::string& playerName, int score, int totalQuestions) {
    const std::string BLUE = "\033[1;34m";
    const std::string GREEN = "\033[1;32m";
    const std::string WHITE = "\033[1;37m";
    const std::string RESET = "\033[0m";
    const int WIDTH = 100;
    std::vector<std::string> lines = {
        BLUE + "🏁 RESULTADOS FINALES" + WHITE,
        WHITE + "Jugador: " + playerName,
        WHITE + "Puntuación: " + std::to_string(score) + "/" + std::to_string(totalQuestions),
        (score >= totalQuestions/2 ? GREEN + "🎉 ¡Felicidades, gran resultado!" + WHITE : BLUE + "¡Sigue practicando!" + WHITE)
    };
    printSectionBox(lines, WIDTH);
    printCenteredNoRightBorder(BLUE + "¿Quieres jugar de nuevo? (Y/N):" + WHITE, WIDTH);
    std::cout << RESET;
}

void displayHappySprite() {
    cout << R"(
║                                                                              ║
║                /\\          /\\                                              ║
║               /||\\        /||\\                                             ║
║              /||||\\      /||||\\                                            ║
║           |||||||||||||||||||||||||||||||                                  ║
║          ||||||||||||||||||||||||||||||                                    ║
║        |||||||||||||||||||||||||||||||||                                   ║
║        |||||||||||||||||||||||||||||||                                     ║
║ /\\     ||||//--\\\\|||||||||||||||||||                                   ║
║/||\\  ||||//|||||||\\|||||||||||||||||                                   ║
║|||||||||||||||||||||||||||||||||||||                                       ║
║|||||||||||||||||||||||||||||||||||||                                       ║
║ ||||||||(______|||||||||||||||||||||                                       ║
║   |||||||||||||||||||||||||||||||                                          ║
║    ||||||||||||||||||||||||||||                                            ║
║        |||||||||||||||||||||\\\\                                           ║
║       //|||||||||||||||||||| \\\\                                          ║
║      /|| ||||||||||||||||||| ||\\                                          ║
║     /!!!  !!!!!!!!!!!!!!!!   !!\\                                         ║
║    //||\\\\  ||||||||||||||   //||\\\\                                    ║
║    \\/  \\/  |||||||||||||||  \\/  \\/                                   ║
║             ||||||||||||||                                                ║
║             |||       |||                                                  ║
║             |||       |||                                                  ║
║             |||       |||                                                  ║
║           {[    ]     {[   ]                                               ║
)";
}

void displayAngrySprite() {
    cout << R"(
║                                                                              ║
║                /\\          /\\                                              ║
║               /||\\        /||\\                                             ║
║              /||||\\      /||||\\                                            ║
║           |||||||||||||||||||||||||||||||                                  ║
║          ||||||||||||||||||||||||||||||||                                  ║
║        |||||||//////||||||||||||||||||||                                   ║
║        |||||||||||||||||||||||||||||||                                     ║
║ /\\     ||||     |||||||||||||||||||||||                                   ║
║/||\\  ||||||     |||||||||||||||||||||                                   ║
║|||||||||||||||||||||||||||||||||||||                                       ║
║|||||||||||||||||||||||||||||||||||||                                       ║
║ |||||||||______|||||||||||||||||||||                                       ║
║   |||||||||||||||||||||||||||||||                                          ║
║    ||||||||||||||||||||||||||||                                            ║
║        |||||||||||||||||||||\\\\                                           ║
║       //|||||||||||||||||||| \\\\                                          ║
║      /|| ||||||||||||||||||| ||\\                                          ║
║     /!!!  !!!!!!!!!!!!!!!!   !!\\                                         ║
║    //||\\\\  ||||||||||||||   //||\\\\                                    ║
║    \\/  \\/  |||||||||||||||  \\/  \\/                                   ║
║             ||||||||||||||                                                ║
║             |||       |||                                                  ║
║             |||       |||                                                  ║
║             |||       |||                                                  ║
║           {[    ]     {[   ]                                               ║
)";
}

void displayPlayerRegistration() {
    const std::string BLUE = "\033[1;34m";
    const std::string CYAN = "\033[0;36m";
    const std::string WHITE = "\033[1;37m";
    const std::string RESET = "\033[0m";
    const int WIDTH = 100;
    std::vector<std::string> lines = {
        BLUE + "👤 REGISTRO DE JUGADOR" + WHITE,
        "",
        CYAN + "Por favor, ingresa tu nombre y apellido para comenzar." + WHITE
    };
    printSectionBox(lines, WIDTH);
    std::cout << RESET;
}

std::string colorizeHangmanWord(const std::string& secret, const std::string& guessed) {
    const std::string GREEN = "\033[1;32m";
    const std::string WHITE = "\033[1;37m";
    std::string result;
    for (size_t i = 0; i < guessed.size(); ++i) {
        if (guessed[i] != '_')
            result += GREEN + guessed.substr(i,1) + WHITE + " ";
        else
            result += WHITE + "_ ";
    }
    return result;
}

std::string colorizeHangmanWrong(const std::vector<char>& wrong) {
    const std::string RED = "\033[1;31m";
    std::string result;
    for (char c : wrong) {
        result += RED + std::string(1, c) + " ";
    }
    return result.empty() ? "-" : result;
}

void displayHangmanState(const std::string& hangmanArt, const std::string& guessedWord, const std::vector<char>& wrongGuesses, int attemptsLeft) {
    const std::string CYAN = "\033[0;36m";
    const std::string WHITE = "\033[1;37m";
    const std::string RESET = "\033[0m";
    const int WIDTH = 100;
    std::vector<std::string> lines = {
        CYAN + "🎩 HANGMAN (AHORCADO)" + WHITE,
        "",
        hangmanArt,
        WHITE + std::string("Palabra: ") + colorizeHangmanWord(guessedWord, guessedWord),
        WHITE + std::string("Letras incorrectas: ") + colorizeHangmanWrong(wrongGuesses),
        WHITE + std::string("Intentos restantes: ") + std::to_string(attemptsLeft) + RESET
    };
    printSectionBox(lines, WIDTH);
}

void displayHangmanMessage(const std::string& msg, const std::string& color = "\033[1;37m") {
    const int WIDTH = 100;
    std::vector<std::string> lines = { color + msg + "\033[0m" };
    printSectionBox(lines, WIDTH);
}

void displayRPSRound(int round) {
    const std::string CYAN = "\033[0;36m";
    const std::string WHITE = "\033[1;37m";
    const int WIDTH = 100;
    std::vector<std::string> lines = {
        CYAN + "✊✋✌️ PIEDRA, PAPEL O TIJERAS" + WHITE,
        CYAN + "Ronda " + std::to_string(round) + " de 3" + WHITE
    };
    printSectionBox(lines, WIDTH);
}

void displayRPSHands(const std::string* left, const std::string* right, int playerMove, int computerMove) {
    const std::string CYAN = "\033[0;36m";
    const std::string WHITE = "\033[1;37m";
    const int WIDTH = 100;
    std::vector<std::string> lines = {
        CYAN + "Tú eliges: " + WHITE + (playerMove == 0 ? "✊" : playerMove == 1 ? "✋" : "✌️") +
        CYAN + "    VS    " + WHITE + (computerMove == 0 ? "✊" : computerMove == 1 ? "✋" : "✌️")
    };
    // Añadir arte ASCII
    for (int i = 0; i < 6; ++i) {
        lines.push_back(WHITE + left[i] + "     " + right[i]);
    }
    printSectionBox(lines, WIDTH);
}

void displayRPSMessage(const std::string& msg, const std::string& color = "\033[1;37m") {
    const int WIDTH = 100;
    std::vector<std::string> lines = { color + msg + "\033[0m" };
    printSectionBox(lines, WIDTH);
}

std::string colorizeTicTacToeCell(char c) {
    std::string content;
    if (c == 'X') content = "\033[1;34mX\033[0m";
    else if (c == 'O') content = "\033[1;31mO\033[0m";
    else content = " ";
    // Centrar en 3 espacios
    return " " + content + " ";
}

void displayTicTacToeBoard(const std::vector<char>& board) {
    // Tablero simple alineado a la izquierda, sin caja ni centrado
    std::cout << "\n   TIC-TAC-TOE\n";
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            int idx = i * 3 + j;
            char c = board[idx];
            if (c == ' ') {
                // Muestra el número de la casilla si está vacía
                std::cout << " " << (idx + 1) << " ";
            } else if (c == 'X') {
                std::cout << " \033[1;34mX\033[0m ";
            } else if (c == 'O') {
                std::cout << " \033[1;31mO\033[0m ";
            }
            if (j < 2) std::cout << "|";
        }
        std::cout << "\n";
        if (i < 2) std::cout << "---+---+---\n";
    }
    std::cout << std::endl;
}

void displayTicTacToeMessage(const std::string& msg, const std::string& color = "\033[1;37m") {
    const int WIDTH = 100;
    std::vector<std::string> lines = { color + msg + "\033[0m" };
    printSectionBox(lines, WIDTH);
}