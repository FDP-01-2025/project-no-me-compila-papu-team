#ifndef POWERUP_H
#define POWERUP_H

#include <string>

enum PowerType {
    DOUBLE_POINTS,
    REDUCED_OPTIONS,
    EXTRA_LIFE,
    REVEAL_HINT,
    NONE
};

class PowerUp {
private:
    PowerType type;

public:
    PowerUp();
    void choosePower();           // Muestra opciones y asigna el tipo
    void applyEffect();           // Muestra el efecto activado
    PowerType getType() const;    // Get type for use in trivia logic
    std::string getPowerName() const; // Nombre legible del power-up
};

#endif