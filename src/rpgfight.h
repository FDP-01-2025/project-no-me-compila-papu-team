#ifndef RPGFIGHT_H
#define RPGFIGHT_H

#include <iostream>
#include <string>

class RpgFight {
private:
    struct Stats {
        int life;
        int attack;
        int defense;
        int critticPercentage;
    };
    
    struct EnemyStats {
        int enemyLife;
        int enemyDamage;
        int enemyDefense;
    };
    
    Stats playerStats;
    EnemyStats enemyStats;
    int difficulty;
    
    void displaySprite();
    void setStats(int difficulty);
    void displayBattleScene();
    
public:
    RpgFight();
    void startGame();
    void setDifficulty(int diff);
    void displayMenu();
};

#endif // RPGFIGHT_H 