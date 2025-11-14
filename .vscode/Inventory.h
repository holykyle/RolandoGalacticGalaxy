#ifndef INVENTORY_H
#define INVENTORY_H

#include <string>
#include <vector>
#include <random>
#include <cmath>

using namespace std;

struct Item {
    string name;
    int quantity;

    Item(const string& n, int q) : name(n), quantity(q) {}
};

class Inventory {
private:
    vector<Item> items;        // DYNAMIC ARRAY

    int gold = 0;

    int bossDropOneCount = 0;  // lifesteal unlock (if you use later)
    int bossDropTwoCount = 0;  // damage multiplier (if you use later)
    double multiplier = 1.0;

    mt19937 gen{ random_device{}() };

public:
    Inventory() {
        // start with 1 HP potion and 1 MP potion
        addItem("Healing Potion", 1);
        addItem("Mana Potion", 1);
    }

    // dynamic array helpers
    void addItem(const string& name, int qty = 1) {
        for (auto& item : items) {
            if (item.name == name) {
                item.quantity += qty;
                return;
            }
        }
        items.emplace_back(name, qty);
    }

    int getItemCount(const string& name) const {
        for (const auto& item : items) {
            if (item.name == name) return item.quantity;
        }
        return 0;
    }

    int useItem(const string& name) {
        for (auto& item : items) {
            if (item.name == name) {
                if (item.quantity <= 0) return 0;
                item.quantity--;
                if (name == "Healing Potion") return 50;
                if (name == "Mana Potion")    return 50;
            }
        }
        return 0;
    }

    int getItemOneCount() const { return getItemCount("Healing Potion"); }
    int getItemTwoCount() const { return getItemCount("Mana Potion"); }

    int useItemOne() { return useItem("Healing Potion"); }
    int useItemTwo() { return useItem("Mana Potion"); }

    int getGold() const { return gold; }
    void addGold(int amount) { gold += amount; }

    // This acts like "addGold" too, matching how you're using it (reward)
    void setGold(int amount) { gold += amount; }

    int getBossDropOneCount() const { return bossDropOneCount; }
    int getBossDropTwoCount() const { return bossDropTwoCount; }

    void incBossDropOneCount() { bossDropOneCount++; }
    void incBossDropTwoCount() { bossDropTwoCount++; }

    bool hasBossDropOne() const { return bossDropOneCount > 0; }
    bool hasBossDropTwo() const { return bossDropTwoCount > 0; }

    int BossDropTwoEffect(int damage) {
        uniform_real_distribution<> dist(1.8, 2.0);
        multiplier = dist(gen);
        double result = damage * multiplier;
        return static_cast<int>(ceil(result));
    }

    double getMultiplier() const { return multiplier; }
};

#endif
