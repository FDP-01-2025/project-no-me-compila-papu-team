#include "PowerUp.h"
#include <iostream>

using namespace std;

PowerUp::PowerUp() : type(NONE) {}

void PowerUp::choosePower() {
    cout << "\n You won the mini-game! Choose your Power-Up:\n";
    cout << "1. DOUBLE POINTS\n";
    cout << "2. REDUCED OPTIONS\n";
    cout << "3. EXTRA LIFE\n";
    cout << "4. REVEAL HINT\n";

    int choice;
    while (true) {
        cout << "Enter your choice (1-4): ";
        cin >> choice;
        if (choice >= 1 && choice <= 4) break;
        cout << "Invalid option. Try again.\n";
    }

    type = static_cast<PowerType>(choice - 1);
}

void PowerUp::applyEffect() {
    cout << "\n Power-Up Activated: " << getPowerName() << "!\n";
    switch (type) {
        case DOUBLE_POINTS:
            cout << "Correct answers will now give DOUBLE points!\n";
            break;
        case REDUCED_OPTIONS:
            cout << "Only two answer options will be shown per question!\n";
            break;
        case EXTRA_LIFE:
            cout << "You get one extra life if you miss a question!\n";
            break;
        case REVEAL_HINT:
            cout << "Hints will be shown during each trivia question!\n";
            break;
        default:
            break;
    }
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