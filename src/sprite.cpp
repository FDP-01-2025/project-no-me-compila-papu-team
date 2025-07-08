#include "SpriteDisplay.h"
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void displayWelcomeMessage() {
    clearScreen();
    // Códigos ANSI para colores
    const std::string YELLOW = "\033[1;33m";
    const std::string CYAN = "\033[1;36m";
    const std::string MAGENTA = "\033[1;35m";
    const std::string WHITE = "\033[1;37m";
    const std::string RESET = "\033[0m";

    cout << WHITE;
    cout << "┌"; for (int i = 0; i < 76; ++i) cout << "─"; cout << "┐\n";
    cout << "│" << YELLOW << "  🎮 QUIEN QUIERE DEJAR DE SER POBRE? 🎯" << WHITE; for (int i = 0; i < 78-36; ++i) cout << " "; cout << "│\n";
    cout << "│" << CYAN << "  Game Collection" << WHITE; for (int i = 0; i < 78-19; ++i) cout << " "; cout << "│\n";
    cout << "├"; for (int i = 0; i < 76; ++i) cout << "─"; cout << "┤\n";
    cout << "│" << MAGENTA << "  🎉 ¡Bienvenido a nuestra emocionante colección de juegos! 🎉" << WHITE; for (int i = 0; i < 78-56; ++i) cout << " "; cout << "│\n";
    cout << "│" << MAGENTA << "  🎯 ¡Juega, gana puntos y deja de ser pobre en conocimiento! 🎯" << WHITE; for (int i = 0; i < 78-59; ++i) cout << " "; cout << "│\n";
    cout << "├"; for (int i = 0; i < 76; ++i) cout << "─"; cout << "┤\n";
    cout << "│  " << CYAN << "🧠 Trivia Challenge: Pon a prueba tus habilidades en Ciencia y Tech" << WHITE; for (int i = 0; i < 78-66; ++i) cout << " "; cout << "│\n";
    cout << "│  " << CYAN << "🎲 Mini-Games Galore: Piedra–Papel–Tijeras, TicTacToe, Hangman..." << WHITE; for (int i = 0; i < 78-70; ++i) cout << " "; cout << "│\n";
    cout << "│  " << CYAN << "⚡ Power-Ups: ¡Gana mini-juegos y obtén ventajas increíbles!" << WHITE; for (int i = 0; i < 78-62; ++i) cout << " "; cout << "│\n";
    cout << "│  " << CYAN << "🏆 Sistema de Puntuación: ¡Compite por el mejor score!" << WHITE; for (int i = 0; i < 78-56; ++i) cout << " "; cout << "│\n";
    cout << "└"; for (int i = 0; i < 76; ++i) cout << "─"; cout << "┘\n";
    cout << YELLOW << "\n  🎮 Presiona cualquier tecla para comenzar tu viaje... 🎮\n" << RESET;
}

void displayMainMenu() {
    clearScreen();
    cout << R"(
╔══════════════════════════════════════════════════════════════════════════════╗
║                    🎮 QUIEN QUIERE DEJAR DE SER POBRE? 🎯                  ║
╠══════════════════════════════════════════════════════════════════════════════╣
║                                                                              ║
║  🎯 1. JUGAR - ¡Comienza tu viaje para dejar de ser pobre! 🚀              ║
║  📊 2. VER PUNTUACIONES - Revisa tu progreso y estadísticas 📈              ║
║  🏆 3. LÍDERES - Top 10 jugadores con mejores puntuaciones 👑               ║
║  ⚙️  4. CONFIGURACIÓN - Personaliza tu experiencia de juego 🔧              ║
║  🚪 5. SALIR - Abandona el juego (¡pero vuelve pronto!) 👋                 ║
║                                                                              ║
╚══════════════════════════════════════════════════════════════════════════════╝
║                                                                              ║
║  🎮 Tu elección: )";
}

void displayDifficultyMenu() {
    cout << R"(
╔══════════════════════════════════════════════════════════════════════════════╗
║                              🎯 SELECCIÓN DE DIFICULTAD 🎯                  ║
╠══════════════════════════════════════════════════════════════════════════════╣
║                                                                              ║
║  🟢 F - FÁCIL: Preguntas básicas para principiantes 🌱                      ║
║  🟡 M - MEDIO: Preguntas intermedias para jugadores experimentados ⚡        ║
║  🔴 A - AVANZADO: Preguntas difíciles para expertos 🧠                      ║
║                                                                              ║
╚══════════════════════════════════════════════════════════════════════════════╝
║                                                                              ║
║  🎯 Selecciona tu nivel: )";
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
    cout << "\n";
    cout << "╔══════════════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                              🎉 ¡CORRECTO! 🎉                              ║\n";
    cout << "║                              ⭐ +1 Punto ⭐                                ║\n";
    cout << "╚══════════════════════════════════════════════════════════════════════════════╝\n";
    
    // Animación de celebración
    for (int i = 0; i < 3; i++) {
        cout << "    🎊";
        this_thread::sleep_for(chrono::milliseconds(200));
        cout << " 🎊";
        this_thread::sleep_for(chrono::milliseconds(200));
        cout << " 🎊\n";
        this_thread::sleep_for(chrono::milliseconds(300));
    }
    
    cout << "\n🎮 Presiona cualquier tecla para continuar...";
}

void displayIncorrectAnswer(const string& correctAnswer) {
    cout << "\n";
    cout << "╔══════════════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                              ❌ ¡INCORRECTO! ❌                            ║\n";
    cout << "║                              💡 Respuesta correcta: " << correctAnswer << " 💡                    ║\n";
    cout << "╚══════════════════════════════════════════════════════════════════════════════╝\n";
    
    cout << "\n😔 Presiona cualquier tecla para continuar...";
}

void displayPowerUpMenu() {
    cout << R"(
╔══════════════════════════════════════════════════════════════════════════════╗
║                              ⚡ POWER-UP DISPONIBLE ⚡                       ║
╠══════════════════════════════════════════════════════════════════════════════╣
║                                                                              ║
║  🎯 1. DOBLE PUNTOS - ¡Gana 2 puntos en lugar de 1! ⭐⭐                   ║
║  🎲 2. OPCIONES REDUCIDAS - Solo 2 opciones en la siguiente pregunta 🎲    ║
║  💖 3. VIDA EXTRA - ¡Obtén una segunda oportunidad! 💖                     ║
║  💡 4. REVELAR PISTA - ¡Obtén una pista para la siguiente pregunta! 💡     ║
║                                                                              ║
╚══════════════════════════════════════════════════════════════════════════════╝
║                                                                              ║
║  🎮 Selecciona tu power-up (1-4): )";
}

void displayMiniGameIntro(const string& gameName) {
    cout << R"(
╔══════════════════════════════════════════════════════════════════════════════╗
║                              🎲 ¡MINI-JUEGO! 🎲                             ║
╠══════════════════════════════════════════════════════════════════════════════╣
║                                                                              ║
║  🎮 Es hora de jugar: )" << gameName << R"(
║  🏆 ¡Gana para obtener un POWER-UP! 🏆                                      ║
║  ⚡ ¡Pierde y continúa sin ventajas! ⚡                                      ║
║                                                                              ║
╚══════════════════════════════════════════════════════════════════════════════╝
║                                                                              ║
║  🎮 Presiona cualquier tecla para comenzar... )";
}

void displayFinalResults(const string& playerName, int score, int totalQuestions) {
    clearScreen();
    cout << R"(
╔══════════════════════════════════════════════════════════════════════════════╗
║                              🏆 RESULTADOS FINALES 🏆                       ║
╠══════════════════════════════════════════════════════════════════════════════╣
║                                                                              ║
║  👤 Jugador: )" << playerName << R"(
║  📊 Puntuación: " << score << "/" << totalQuestions << " puntos 📊
║  📈 Porcentaje: )" << (score * 100 / totalQuestions) << R"(% 📈
║                                                                              ║
)";
    
    if (score >= totalQuestions / 2) {
        cout << "║  🎉 ¡EXCELENTE TRABAJO! ¡Has dejado de ser pobre en conocimiento! 🎉      ║\n";
        displayHappySprite();
    } else {
        cout << "║  😔 ¡Sigue practicando! El conocimiento es la clave del éxito! 😔        ║\n";
        displayAngrySprite();
    }
    
    cout << R"(
║                                                                              ║
╚══════════════════════════════════════════════════════════════════════════════╝
║                                                                              ║
║  🎮 ¿Quieres jugar de nuevo? (Y/N): )";
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