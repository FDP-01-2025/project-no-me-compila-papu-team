#include "PowerUp.h"
#include "SpriteDisplay.h"
#include <iostream>

using namespace std;

PowerUp::PowerUp() : type(NONE) {}

void PowerUp::choosePower() {
    int choice;
    while (true) {
        cin >> choice;
        if (choice >= 1 && choice <= 4) break;
        cout << "Invalid option. Try again.\n";
    }
    type = static_cast<PowerType>(choice - 1);
}

void PowerUp::applyEffect() {
    cout << "\n╔══════════════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                              ⚡ POWER-UP ACTIVADO ⚡                         ║\n";
    cout << "╠══════════════════════════════════════════════════════════════════════════════╣\n";
    cout << "║                                                                              ║\n";
    cout << "║  🎯 " << getPowerName() << " ha sido activado! 🎯                          ║\n";
    cout << "║                                                                              ║\n";
    
    switch (type) {
        case DOUBLE_POINTS:
            cout << "║  ⭐ ¡Las respuestas correctas ahora darán DOBLE puntos! ⭐              ║\n";
            break;
        case REDUCED_OPTIONS:
            cout << "║  🎲 ¡Solo se mostrarán dos opciones de respuesta por pregunta! 🎲    ║\n";
            break;
        case EXTRA_LIFE:
            cout << "║  💖 ¡Obtienes una vida extra si fallas una pregunta! 💖              ║\n";
            break;
        case REVEAL_HINT:
            cout << "║  💡 ¡Se mostrarán pistas durante cada pregunta de trivia! 💡          ║\n";
            break;
        default:
            break;
    }
    
    cout << "║                                                                              ║\n";
    cout << "╚══════════════════════════════════════════════════════════════════════════════╝\n";
    cout << "\n🎮 Presiona cualquier tecla para continuar...";
}

PowerType PowerUp::getType() const {
    return type;
}

string PowerUp::getPowerName() const {
    switch (type) {
        case DOUBLE_POINTS: return "DOUBLE POINTS";
        case REDUCED_OPTIONS: return "REDUCED OPTIONS";
        case EXTRA_LIFE: return "EXTRA LIFE";
        case REVEAL_HINT: return "REVEAL HINT";
        default: return "NONE";
    }
}