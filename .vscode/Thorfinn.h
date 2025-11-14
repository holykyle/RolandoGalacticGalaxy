#ifndef THORFINN_H
#define THORFINN_H

#include "Player.h"
#include <cstdlib>

using namespace std;

class Thorfinn : public Player {
    string s1 = "Whirlwind Cleave";
    string s2 = "Seismic Strike";
    string s3 = "Blade Tempest";

public:
    Thorfinn(const string& name, int hp, int mp, int xp)
        : Player(name, hp, mp, xp) {}

    int skillOne() override {
        return rand() % (40 - 30 + 1) + 30; // 30–40
    }

    int skillTwo() override {
        return rand() % (45 - 35 + 1) + 35; // 35–45
    }

    int skillThree() override {
        return rand() % (50 - 45 + 1) + 45; // 45–50
    }

    int oneHitDelete() override {
        cout << "Thorfinn uses One Hit Delete! Deals INFINITE damage!\n";
        return 1000;
    }

    string skillOneName()   const override { return s1; }
    string skillTwoName()   const override { return s2; }
    string skillThreeName() const override { return s3; }
};

#endif
