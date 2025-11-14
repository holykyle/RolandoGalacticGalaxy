#ifndef MINION_H
#define MINION_H

#include "Enemy.h"
#include <iostream>
#include <sstream>

using namespace std;

class Minion : public Enemy {
protected:
    int health;
    int maxHealth;
    string name;

public:
    Minion(const string& n, int maxHp)
        : health(maxHp), maxHealth(maxHp), name(n) {}

    void takeDamage(int dmg) override {
        health -= dmg;
        if (health < 0) health = 0;
    }

    int getHealth() const override { return health; }
    string getName() const override { return name; }

    string toString() const override {
        int barLength = 20;
        int filled    = (int)((double)health / maxHealth * barLength);

        const string RED   = "\u001B[31m";
        const string RESET = "\u001B[0m";

        stringstream ss;
        ss << name << "'s Health: " << health << "/" << maxHealth << " [";
        for (int i = 0; i < barLength; ++i) {
            if (i < filled) {
                ss << RED << "█" << RESET;
            } else {
                ss << " ";
            }
        }
        ss << "]\n\n";
        return ss.str();
    }
};

#endif
