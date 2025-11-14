#ifndef ENEMIES_H
#define ENEMIES_H

#include "Minion.h"
#include "Enemy.h"
#include <cstdlib>
#include <iostream>
#include <sstream>

using namespace std;

// ----------------------------- Minions -----------------------------

class Mare : public Minion {
public:
    Mare(const string& name, int maxHp)
        : Minion(name, maxHp) {}

    int skillOne() override {
        int dmg = rand() % (25 - 10 + 1) + 10;
        cout << "Mare uses Nightmare Lash! Deals " << dmg << " damage.\n";
        return dmg;
    }
    int skillTwo() override { return 0; }
    int skillThree() override { return 0; }
};

class Draugar : public Minion {
public:
    Draugar(const string& name, int maxHp)
        : Minion(name, maxHp) {}

    int skillOne() override {
        int dmg = rand() % (25 - 10 + 1) + 10;
        cout << "Draugar uses Scratch! Deals " << dmg << " damage.\n";
        return dmg;
    }
    int skillTwo() override { return 0; }
    int skillThree() override { return 0; }
};

class Fossegrimen : public Minion {
public:
    Fossegrimen(const string& name, int maxHp)
        : Minion(name, maxHp) {}

    int skillOne() override {
        int dmg = rand() % (25 - 10 + 1) + 10;
        cout << "Fossegrimen uses River Song! Deals " << dmg << " damage.\n";
        return dmg;
    }
    int skillTwo() override { return 0; }
    int skillThree() override { return 0; }
};

class Anzu : public Minion {
public:
    Anzu(const string& name, int maxHp)
        : Minion(name, maxHp) {}

    int skillOne() override {
        int dmg = rand() % (25 - 10 + 1) + 10;
        cout << "Anzu uses Storm Talon! Deals " << dmg << " damage.\n";
        return dmg;
    }
    int skillTwo() override { return 0; }
    int skillThree() override { return 0; }
};

class Hyosube : public Minion {
public:
    Hyosube(const string& name, int maxHp)
        : Minion(name, maxHp) {}

    int skillOne() override {
        int dmg = rand() % (25 - 10 + 1) + 10;
        cout << "Hyosube uses Frost Claw! Deals " << dmg << " damage.\n";
        return dmg;
    }
    int skillTwo() override { return 0; }
    int skillThree() override { return 0; }
};

class Urmahlullu : public Minion {
public:
    Urmahlullu(const string& name, int maxHp)
        : Minion(name, maxHp) {}

    int skillOne() override {
        int dmg = rand() % (25 - 10 + 1) + 10;
        cout << "Urmahlullu uses Feral Charge! Deals " << dmg << " damage.\n";
        return dmg;
    }
    int skillTwo() override { return 0; }
    int skillThree() override { return 0; }
};

class Kappa : public Minion {
public:
    Kappa(const string& name, int maxHp)
        : Minion(name, maxHp) {}

    int skillOne() override {
        int dmg = rand() % (25 - 10 + 1) + 10;
        cout << "Kappa uses Swamp Grasp! Deals " << dmg << " damage.\n";
        return dmg;
    }
    int skillTwo() override { return 0; }
    int skillThree() override { return 0; }
};

class Jormungandr : public Minion {
public:
    Jormungandr(const string& name, int maxHp)
        : Minion(name, maxHp) {}

    int skillOne() override {
        int dmg = rand() % (35 - 20 + 1) + 20;
        cout << "Jormungandr uses Venomous Coil! Deals " << dmg << " damage.\n";
        return dmg;
    }
    int skillTwo() override {
        int dmg = rand() % (45 - 30 + 1) + 30;
        cout << "Jormungandr uses Ocean Crush! Deals " << dmg << " damage.\n";
        return dmg;
    }
    int skillThree() override {
        int dmg = rand() % (55 - 40 + 1) + 40;
        cout << "Jormungandr uses World’s End! Deals " << dmg << " damage.\n";
        return dmg;
    }
};

// ----------------------------- Bosses -----------------------------

class KrevMalak : public Enemy {
    int health;
    int maxHealth;
    string name;
public:
    KrevMalak(const string& n, int maxHp)
        : health(maxHp), maxHealth(maxHp), name(n) {}

    int skillOne() override {
        int dmg = rand() % (30 - 20 + 1) + 20;
        cout << "Krev Malak uses Shadow Rupture! Deals " << dmg << " damage.\n";
        return dmg;
    }
    int skillTwo() override {
        int dmg = rand() % (40 - 25 + 1) + 25;
        cout << "Krev Malak uses Abyssal Lance! Deals " << dmg << " damage.\n";
        return dmg;
    }
    int skillThree() override {
        int dmg = rand() % (55 - 35 + 1) + 35;
        cout << "Krev Malak uses Void Collapse! Deals " << dmg << " damage.\n";
        return dmg;
    }

    void takeDamage(int dmg) override {
        health -= dmg;
        if (health < 0) health = 0;
    }
    int getHealth() const override { return health; }
    string getName() const override { return name; }

    string toString() const override {
        int barLength = 30;
        int filled    = (int)((double)health / maxHealth * barLength);
        const string RED   = "\u001B[31m";
        const string RESET = "\u001B[0m";
        stringstream ss;
        ss << name << "'s Health: " << health << "/" << maxHealth << " [";
        for (int i = 0; i < barLength; ++i) {
            if (i < filled) ss << RED << "█" << RESET;
            else            ss << " ";
        }
        ss << "]\n\n";
        return ss.str();
    }
};

class Humbaba : public Enemy {
    int health;
    int maxHealth;
    string name;
public:
    Humbaba(const string& n, int maxHp)
        : health(maxHp), maxHealth(maxHp), name(n) {}

    int skillOne() override {
        int dmg = rand() % (25 - 15 + 1) + 15;
        cout << "Humbaba uses Thunder Stomp! Deals " << dmg << " damage.\n";
        return dmg;
    }
    int skillTwo() override {
        int dmg = rand() % (35 - 20 + 1) + 20;
        cout << "Humbaba uses Mountain Roar! Deals " << dmg << " damage.\n";
        return dmg;
    }
    int skillThree() override {
        int dmg = rand() % (50 - 30 + 1) + 30;
        cout << "Humbaba uses Titan Crush! Deals " << dmg << " damage.\n";
        return dmg;
    }

    void takeDamage(int dmg) override {
        health -= dmg;
        if (health < 0) health = 0;
    }
    int getHealth() const override { return health; }
    string getName() const override { return name; }

    string toString() const override {
        int barLength = 30;
        int filled    = (int)((double)health / maxHealth * barLength);
        const string RED   = "\u001B[31m";
        const string RESET = "\u001B[0m";
        stringstream ss;
        ss << name << "'s Health: " << health << "/" << maxHealth << " [";
        for (int i = 0; i < barLength; ++i) {
            if (i < filled) ss << RED << "█" << RESET;
            else            ss << " ";
        }
        ss << "]\n\n";
        return ss.str();
    }
};

class Tiamat : public Enemy {
    int health;
    int maxHealth;
    string name;
public:
    Tiamat(const string& n, int maxHp)
        : health(maxHp), maxHealth(maxHp), name(n) {}

    int skillOne() override {
        int dmg = rand() % (25 - 15 + 1) + 15;
        cout << "Tiamat uses Chaos Wave! Deals " << dmg << " damage.\n";
        return dmg;
    }
    int skillTwo() override {
        int dmg = rand() % (35 - 20 + 1) + 20;
        cout << "Tiamat uses Storm’s Embrace! Deals " << dmg << " damage.\n";
        return dmg;
    }
    int skillThree() override {
        int dmg = rand() % (50 - 30 + 1) + 30;
        cout << "Tiamat uses Celestial Deluge! Deals " << dmg << " damage.\n";
        return dmg;
    }

    void takeDamage(int dmg) override {
        health -= dmg;
        if (health < 0) health = 0;
    }
    int getHealth() const override { return health; }
    string getName() const override { return name; }

    string toString() const override {
        int barLength = 35;
        int filled    = (int)((double)health / maxHealth * barLength);
        const string RED   = "\u001B[31m";
        const string RESET = "\u001B[0m";
        stringstream ss;
        ss << name << "'s Health: " << health << "/" << maxHealth << " [";
        for (int i = 0; i < barLength; ++i) {
            if (i < filled) ss << RED << "█" << RESET;
            else            ss << " ";
        }
        ss << "]\n\n";
        return ss.str();
    }
};

#endif
