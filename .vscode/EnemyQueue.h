#ifndef ENEMY_QUEUE_H
#define ENEMY_QUEUE_H

#include <queue>
#include "Enemy.h"

using namespace std;

class EnemyQueue {
private:
    queue<Enemy*> enemies;  // QUEUE of Enemy pointers

public:
    void addEnemy(Enemy* e) {
        enemies.push(e);
    }

    bool empty() const {
        return enemies.empty();
    }

    Enemy* current() {
        if (enemies.empty()) return nullptr;
        return enemies.front();
    }

    void popCurrent() {
        if (!enemies.empty()) {
            delete enemies.front();  // free memory
            enemies.pop();
        }
    }

    ~EnemyQueue() {
        while (!enemies.empty()) {
            delete enemies.front();
            enemies.pop();
        }
    }
};

#endif
