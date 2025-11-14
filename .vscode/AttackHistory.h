#ifndef ATTACK_HISTORY_H
#define ATTACK_HISTORY_H

#include <stack>
#include <string>
#include <iostream>

using namespace std;

class AttackHistory {
private:
    stack<string> history;  // STACK

public:
    void push(const string& desc) {
        history.push(desc);
    }

    bool empty() const {
        return history.empty();
    }

    string top() const {
        if (history.empty()) return "";
        return history.top();
    }

    void pop() {
        if (!history.empty()) history.pop();
    }

    void printRecent(int count = 5) {
        stack<string> temp = history;
        int printed = 0;
        cout << "\n--- Recent Attacks (Stack) ---\n";
        while (!temp.empty() && printed < count) {
            cout << temp.top() << "\n";
            temp.pop();
            printed++;
        }
        cout << "------------------------------\n";
    }
};

#endif
