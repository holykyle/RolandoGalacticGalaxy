#ifndef WALLS_H
#define WALLS_H

#include <iostream>
#include <limits>
#include <cstdlib>
#include <string>

#include "Player.h"
#include "Inventory.h"
#include "EnemyQueue.h"
#include "AttackHistory.h"
#include "Enemies.h"

using namespace std;

void typeText(const string &text, int delayMs);

// -----------------------------------------------------------------------------
// WallRunner: handles generic wall combat loop
// -----------------------------------------------------------------------------
class WallRunner {
public:
    static bool runWall(
        const string& wallName,
        Player& character,
        Inventory& inv,
        EnemyQueue& enemyQueue,
        AttackHistory& history
    ) {
        cout << "\n=================================================\n";
        typeText("Approaching " + wallName + "...\n", 25);
        typeText("The wreckage grows denser, and hostile signals flare in the dark.\n", 25);
        typeText("Press ENTER to begin your assault.\n", 20);
        typeText("[Press SPACE during text to skip animations]\n\n", 15);

        string dummy;
        getline(cin >> ws, dummy);

        while (!enemyQueue.empty() && character.getHealth() > 0) {
            Enemy* enemy = enemyQueue.current();

            typeText("\nA hostile signal locks onto your hull...\n", 20);
            typeText("A wild " + enemy->getName() + " appears!\n\n", 20);

            while (enemy->getHealth() > 0 && character.getHealth() > 0) {
                typeText(enemy->toString(), 2);
                character.printStatsFromList();

                typeText("Gold: " + to_string(inv.getGold()) + "\n\n", 5);

                typeText("Choose your action:\n", 10);
                typeText("1. " + character.skillOneName()   + " (30-40 dmg, +15 MP)\n", 5);
                typeText("2. " + character.skillTwoName()   + " (dmg, 20 MP, lifesteal)\n", 5);
                typeText("3. " + character.skillThreeName() + " (dmg, 30 MP, lifesteal)\n", 5);
                typeText("4. One Hit Delete\n", 5);
                typeText("5. Healing Potion (" + to_string(inv.getItemOneCount()) + ")\n", 5);
                typeText("6. Mana Potion (" + to_string(inv.getItemTwoCount()) + ")\n", 5);
                typeText("Enter choice: ", 5);

                int choice;
                if (!(cin >> choice)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    typeText("\nInvalid input. Please enter a number.\n", 10);
                    continue;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                int damage      = 0;
                int enemyDamage = 0;
                int heal        = 0;
                int mana        = 0;

                switch (choice) {
                    case 1: {
                        character.addMana();
                        damage = character.skillOne();
                        string msg = character.getName() + " uses " + character.skillOneName()
                                     + " and deals " + to_string(damage) + " damage.\n";
                        typeText(msg, 10);
                        enemy->takeDamage(damage);
                        history.push(msg);
                        break;
                    }

                    case 2:
                        if (character.useMana(20)) {
                            damage = character.skillTwo();
                            character.setHeal(damage / 2);
                            typeText("Lifesteal: +" + to_string(damage / 2) + " HP\n", 10);
                            enemy->takeDamage(damage);
                            history.push(character.getName() + " used " + character.skillTwoName()
                                + " for " + to_string(damage) + " damage (lifesteal).");
                        } else {
                            typeText("Not enough mana!\n", 10);
                            continue;
                        }
                        break;

                    case 3:
                        if (character.useMana(30)) {
                            damage = character.skillThree();
                            character.setHeal(damage / 2);
                            typeText("Lifesteal: +" + to_string(damage / 2) + " HP\n", 10);
                            enemy->takeDamage(damage);
                            history.push(character.getName() + " used " + character.skillThreeName()
                                + " for " + to_string(damage) + " damage (lifesteal).");
                        } else {
                            typeText("Not enough mana!\n", 10);
                            continue;
                        }
                        break;

                    case 4:
                        damage = character.oneHitDelete();
                        enemy->takeDamage(damage);
                        history.push(character.getName() + " used ONE HIT DELETE!");
                        typeText(character.getName() + " unleashes ONE HIT DELETE!\n", 10);
                        break;

                    case 5:
                        if (inv.getItemOneCount() > 0 && character.getHealth() < character.getMaxHealth()) {
                            heal = inv.useItemOne();
                            character.setHeal(heal);
                            typeText("You used a Healing Potion! +" + to_string(heal) + " HP.\n", 10);
                            history.push("Used Healing Potion for +" + to_string(heal) + " HP.");
                        } else {
                            typeText("Cannot use Healing Potion.\n", 10);
                        }
                        continue;

                    case 6:
                        if (inv.getItemTwoCount() > 0 && character.getMana() < character.getMaxMana()) {
                            mana = inv.useItemTwo();
                            character.setMana(mana);
                            typeText("You used a Mana Potion! +" + to_string(mana) + " MP.\n", 10);
                            history.push("Used Mana Potion for +" + to_string(mana) + " MP.");
                        } else {
                            typeText("Cannot use Mana Potion.\n", 10);
                        }
                        continue;

                    default:
                        typeText("Invalid choice. Try again.\n", 10);
                        continue;
                }

                if (enemy->getHealth() > 0) {
                    enemyDamage = enemy->skillOne();
                    character.takeDamage(enemyDamage);
                    string enemyMsg = enemy->getName() + " dealt " + to_string(enemyDamage) + " damage.\n";
                    typeText(enemyMsg, 10);
                    history.push(enemyMsg);
                }

                if (character.getHealth() <= 0) {
                    typeText("\n" + character.getName() + " has fallen...\n", 25);
                    character.setDefeated(true);
                    return false;
                } else if (enemy->getHealth() <= 0) {
                    typeText("\n" + character.getName() + " defeated " + enemy->getName() + "!\n", 20);
                    int goldReward = rand() % (100 - 75 + 1) + 75;
                    int xpReward   = rand() % (25  - 15 + 1) + 15;
                    inv.setGold(goldReward);
                    character.addExp(xpReward);

                    typeText("You earned " + to_string(goldReward) + " gold and "
                             + to_string(xpReward) + " XP.\n", 20);
                    break;
                }
            }

            if (character.getHealth() <= 0) return false;

            enemyQueue.popCurrent();
        }

        typeText("\nYou cleared " + wallName + "!\n", 25);
        history.printRecent();
        return true;
    }
};

// -----------------------------------------------------------------------------
// WALL 1
// -----------------------------------------------------------------------------
class Wall1 {
public:
    bool run(Player& character, Inventory& inv, AttackHistory& history) {
        EnemyQueue eq;
        eq.addEnemy(new Mare("Mare", 100));
        eq.addEnemy(new Draugar("Draugar", 110));
        eq.addEnemy(new Fossegrimen("Fossegrimen", 120));
        return WallRunner::runWall("WALL 1: THE DARK FOREST", character, inv, eq, history);
    }
};

// -----------------------------------------------------------------------------
// WALL 2
// -----------------------------------------------------------------------------
class Wall2 {
public:
    bool run(Player& character, Inventory& inv, AttackHistory& history) {
        EnemyQueue eq;
        eq.addEnemy(new Hyosube("Hyosube", 120));
        eq.addEnemy(new Urmahlullu("Urmahlullu", 130));
        eq.addEnemy(new Kappa("Kappa", 140));
        return WallRunner::runWall("WALL 2: BJORN DAL", character, inv, eq, history);
    }
};

// -----------------------------------------------------------------------------
// WALL 3
// -----------------------------------------------------------------------------
class Wall3 {
public:
    bool run(Player& character, Inventory& inv, AttackHistory& history) {
        EnemyQueue eq;
        eq.addEnemy(new Jormungandr("Jormungandr", 200));
        eq.addEnemy(new KrevMalak("Krev Malak", 220));
        eq.addEnemy(new Humbaba("Humbaba", 240));
        eq.addEnemy(new Tiamat("Tiamat", 300));
        return WallRunner::runWall("WALL 3: THE ABYSSAL GATE", character, inv, eq, history);
    }
};

#endif
