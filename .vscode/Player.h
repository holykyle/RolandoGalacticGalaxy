#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>

using namespace std;

// Linked list node for stats: HP, MP, XP
struct StatNode {
    string label;
    int* value;      // pointer to the actual stat variable
    StatNode* next;

    StatNode(const string& lbl, int* val)
        : label(lbl), value(val), next(nullptr) {}
};

class Player {
protected:
    string name;

    int health;
    int maxHealth;
    int mana;
    int maxMana;
    int exp;

    bool defeated = false;

    // Linked list head for stats
    StatNode* statHead = nullptr;

    void initStatList() {
        // HP -> MP -> XP in linked list
        StatNode* hpNode = new StatNode("HP", &health);
        StatNode* mpNode = new StatNode("MP", &mana);
        StatNode* xpNode = new StatNode("XP", &exp);

        hpNode->next = mpNode;
        mpNode->next = xpNode;
        xpNode->next = nullptr;

        statHead = hpNode;
    }

public:
    Player(const string& name, int hp, int mp, int xp)
        : name(name),
          health(hp), maxHealth(hp),
          mana(mp),   maxMana(mp),
          exp(xp) {
        initStatList();
    }

    virtual ~Player() {
        // free linked list nodes
        StatNode* curr = statHead;
        while (curr) {
            StatNode* nxt = curr->next;
            delete curr;
            curr = nxt;
        }
    }

    // pure virtual skills
    virtual int skillOne() = 0;
    virtual int skillTwo() = 0;
    virtual int skillThree() = 0;
    virtual int oneHitDelete() { return 0; }

    virtual string skillOneName()   const = 0;
    virtual string skillTwoName()   const = 0;
    virtual string skillThreeName() const = 0;

    // getters
    string getName() const { return name; }

    int getHealth() const { return health; }
    int getMaxHealth() const { return maxHealth; }

    int getMana() const { return mana; }
    int getMaxMana() const { return maxMana; }

    int getExp() const { return exp; }

    bool getDefeated() const { return defeated; }
    void setDefeated(bool v) { defeated = v; }

    // damage / healing / mana / xp
    void takeDamage(int dmg) {
        health -= dmg;
        if (health < 0) health = 0;
    }

    void setHeal(int amount) {
        health += amount;
        if (health > maxHealth) health = maxHealth;
    }

    bool useMana(int cost) {
        if (mana < cost) return false;
        mana -= cost;
        return true;
    }

    void setMana(int amount) {
        mana += amount;
        if (mana > maxMana) mana = maxMana;
    }

    void addMana() {
        mana += 15; // basic attack bonus
        if (mana > maxMana) mana = maxMana;
    }

    void addExp(int amount) {
        exp += amount;
        // you can add level-up logic here later
    }

    // show stats using the linked list
    void printStatsFromList() const {
        cout << "\n--- Player Stats (Linked List) ---\n";
        StatNode* curr = statHead;
        while (curr) {
            cout << curr->label << ": " << *(curr->value) << "\n";
            curr = curr->next;
        }
        cout << "----------------------------------\n\n";
    }
};

#endif
