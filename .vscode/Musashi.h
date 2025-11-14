#ifndef MUSASHI_H
#define MUSASHI_H

#include "Player.h"
#include <cstdlib>

using namespace std;

class Musashi : public Player {
    string s1 = "Twin Fang Slash";
    string s2 = "Dragon’s Arc";
    string s3 = "Heavenly Draw";

public:
    Musashi(const string& name, int hp, int mp, int xp)
        : Player(name, hp, mp, xp) {}

    int skillOne() override {
        return rand() % (35 - 25 + 1) + 25; // 25–35
    }

    int skillTwo() override {
        return rand() % (45 - 30 + 1) + 30; // 30–45
    }

    int skillThree() override {
        return rand() % (55 - 40 + 1) + 40; // 40–55
    }

    int oneHitDelete() override {
        cout << "Musashi uses One Hit Delete! Deals INFINITE damage!\n";
        return 1000;
    }

    string skillOneName()   const override { return s1; }
    string skillTwoName()   const override { return s2; }
    string skillThreeName() const override { return s3; }
};

#endif
