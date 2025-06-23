#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <limits>

using namespace std;

class Hangman {
private:
    vector<string> words = {
        "PROGRAMACION", "COMPUTADORA", "ALGORITMO", "VARIABLE", "FUNCION",
        "CLASE", "OBJETO", "HERENCIA", "POLIMORFISMO", "ENCAPSULACION",
        "INTERFAZ", "ABSTRACT", "EXCEPCION", "RECURSION", "ITERACION",
        "ARREGLO", "MATRIZ", "PUNTERO", "REFERENCIA", "TEMPLATE"
    };
    
    string secretWord;
    string hiddenWord;
    vector<char> usedLetters;
    int remainingAttempts;
    const int MAX_ATTEMPTS = 6;
    
    void drawHangman() {
        cout << "\n";
        cout << "  +---+\n";
        cout << "  |   |\n";
        
        if (remainingAttempts < 6) {
            cout << "  O   |\n";
        } else {
            cout << "      |\n";
        }
        
        if (remainingAttempts < 5) {
            cout << " /|\\  |\n";
        } else if (remainingAttempts < 6) {
            cout << " /|   |\n";
        } else {
            cout << "      |\n";
        }
        
        if (remainingAttempts < 4) {
            cout << " / \\  |\n";
        } else if (remainingAttempts < 5) {
            cout << " /    |\n";
        } else {
            cout << "      |\n";
        }
        
        cout << "      |\n";
        cout << "=========\n";
    }
    
    void showHiddenWord() {
        cout << "\nPalabra: ";
        for (char c : hiddenWord) {
            cout << c << " ";
        }
        cout << "\n";
    }
    
    void showUsedLetters() {
        cout << "Letras usadas: ";
        for (char c : usedLetters) {
            cout << c << " ";
        }
        cout << "\n";
    }
    
    void showAttempts() {
        cout << "Intentos restantes: " << remainingAttempts << "/" << MAX_ATTEMPTS << "\n";
    }
    
    bool letterInWord(char letter) {
        return secretWord.find(toupper(letter)) != string::npos;
    }
    
    void revealLetter(char letter) {
        for (size_t i = 0; i < secretWord.length(); i++) {
            if (toupper(secretWord[i]) == toupper(letter)) {
                hiddenWord[i] = secretWord[i];
            }
        }
    }
    
    bool wordComplete() {
        return hiddenWord == secretWord;
    }
    
public:
    Hangman() {
        srand(time(0));
        resetGame();
    }
    
    void resetGame() {
        // pick a random word from our list
        secretWord = words[rand() % words.size()];
        
        // hide it with underscores
        hiddenWord = string(secretWord.length(), '_');
        
        // clear the used letters list
        usedLetters.clear();
        
        // give player full attempts back
        remainingAttempts = MAX_ATTEMPTS;
    }
    
    void play() {
        cout << "=== JUEGO DEL AHORCADO ===\n";
        cout << "¡Adivina la palabra antes de que se complete el ahorcado!\n\n";
        
        while (remainingAttempts > 0 && !wordComplete()) {
            // show current game state
            drawHangman();
            showHiddenWord();
            showUsedLetters();
            showAttempts();
            
            // get letter from player
            char letter;
            cout << "\nIngresa una letra: ";
            cin >> letter;
            
            // make sure it's actually a letter
            if (!isalpha(letter)) {
                cout << "Por favor ingresa una letra válida.\n";
                continue;
            }
            
            letter = toupper(letter);
            
            // check if they already tried this letter
            if (find(usedLetters.begin(), usedLetters.end(), letter) != usedLetters.end()) {
                cout << "Ya usaste esa letra. Intenta con otra.\n";
                continue;
            }
            
            // add to used letters list
            usedLetters.push_back(letter);
            
            // see if they got it right
            if (letterInWord(letter)) {
                cout << "¡Correcto! La letra '" << letter << "' está en la palabra.\n";
                revealLetter(letter);
            } else {
                cout << "Incorrecto. La letra '" << letter << "' no está en la palabra.\n";
                remainingAttempts--;
            }
            
            cout << "\n" << string(50, '-') << "\n";
        }
        
        // show final result
        drawHangman();
        showHiddenWord();
        
        if (wordComplete()) {
            cout << "\n¡FELICIDADES! ¡HAS GANADO!\n";
            cout << "Adivinaste la palabra: " << secretWord << "\n";
        } else {
            cout << "\n¡GAME OVER! Has perdido.\n";
            cout << "La palabra era: " << secretWord << "\n";
        }
    }
    
    void showMenu() {
        while (true) {
            cout << "\n=== MENÚ PRINCIPAL ===\n";
            cout << "1. Jugar\n";
            cout << "2. Salir\n";
            cout << "Selecciona una opción: ";
            
            int option;
            cin >> option;
            
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Opción inválida. Intenta de nuevo.\n";
                continue;
            }
            
            switch (option) {
                case 1:
                    resetGame();
                    play();
                    break;
                case 2:
                    cout << "¡Gracias por jugar! ¡Hasta luego!\n";
                    return;
                default:
                    cout << "Opción inválida. Intenta de nuevo.\n";
                    break;
            }
        }
    }
};

int main() {
    Hangman game;
    game.showMenu();
    return 0;
}
