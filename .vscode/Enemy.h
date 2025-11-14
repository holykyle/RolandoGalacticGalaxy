#ifndef ENEMY_H
#define ENEMY_H

#include <string>

using namespace std;

class Enemy {
public:
    virtual ~Enemy() = default;

    virtual int  skillOne()   = 0;
    virtual int  skillTwo()   = 0;
    virtual int  skillThree() = 0;

    virtual void   takeDamage(int dmg) = 0;
    virtual int    getHealth()   const = 0;
    virtual string getName()     const = 0;
    virtual string toString()    const = 0;
};

#endif
