#ifndef SHOP_H
#define SHOP_H

#include <iostream>
#include <limits>
#include <string>
#include "Inventory.h"

using namespace std;

// Use the same typewriter function
void typeText(const string &text, int delayMs);

class Shop {
public:
    void open(Inventory& inv) {
        int choice = 0;
        do {
            typeText("\n===== SHOP =====\n", 10);
            typeText("Gold: " + to_string(inv.getGold()) + "\n", 10);
            typeText("1. Buy Healing Potion (50 gold)\n", 5);
            typeText("2. Buy Mana Potion (50 gold)\n", 5);
            typeText("0. Leave Shop\n", 5);
            typeText("Choice: ", 5);

            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                typeText("Invalid input.\n", 10);
                continue;
            }

            if (choice == 1) {
                if (inv.getGold() >= 50) {
                    inv.addGold(-50);
                    inv.addItem("Healing Potion", 1);
                    typeText("Bought 1 Healing Potion.\n", 10);
                } else {
                    typeText("Not enough gold.\n", 10);
                }
            } else if (choice == 2) {
                if (inv.getGold() >= 50) {
                    inv.addGold(-50);
                    inv.addItem("Mana Potion", 1);
                    typeText("Bought 1 Mana Potion.\n", 10);
                } else {
                    typeText("Not enough gold.\n", 10);
                }
            }
        } while (choice != 0);
    }
};

#endif
