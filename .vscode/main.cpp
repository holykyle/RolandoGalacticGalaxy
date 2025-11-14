#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <conio.h>   // for _kbhit and _getch (Windows / MinGW)
#include <limits>

#include "Thorfinn.h"
#include "Musashi.h"
#include "Player.h"
#include "Inventory.h"
#include "AttackHistory.h"
#include "Shop.h"
#include "Walls.h"
#include "Minion.h"
#include "EnemyQueue.h"
#include "Enemy.h"
#include "Enemies.h"

using namespace std;

// -----------------------------------------------------------------------------
// Utility: typewriter-style text with SPACE-to-skip *current* string
// -----------------------------------------------------------------------------
void typeText(const string &text, int delayMs) {
    bool skipThisString = false;

    for (char c : text) {
        cout << c << flush;

        // If already skipping this string or no delay, just continue
        if (skipThisString || delayMs <= 0) {
            continue;
        }

        // Break delay into small chunks so we can detect key presses
        int step = max(1, delayMs / 5);
        int elapsed = 0;
        while (elapsed < delayMs) {
            if (_kbhit()) {
                int ch = _getch();
                if (ch == ' ') {
                    // SPACE: skip the rest of THIS text (but not future ones)
                    skipThisString = true;
                    break;
                }
            }
            this_thread::sleep_for(chrono::milliseconds(step));
            elapsed += step;
        }
    }
}

// -----------------------------------------------------------------------------
// Intro screen
// -----------------------------------------------------------------------------
void showIntro() {
    cout << "=================================================\n";
    cout << "         RROLANDO'S GALACTIC GRAVEYARD\n";
    cout << "=================================================\n\n";

    typeText("In a forgotten corner of the cosmos, wrecked warships drift in silence.\n", 25);
    typeText("They call it the Galactic Graveyard.\n", 25);
    typeText("A forsaken sector where the brave hunt for relics and glory...\n", 25);
    typeText("and the unprepared are never seen again.\n\n", 25);

    typeText("Tonight, a new hunter enters the field.\n", 25);
    typeText("Choose your warrior and carve your legend among the ruins.\n\n", 25);
    typeText("[TIP] Press SPACE during text to skip the animation for that line.\n\n", 15);
}

// -----------------------------------------------------------------------------
// Character selection
// -----------------------------------------------------------------------------
int askCharacterChoice() {
    int choice = 0;

    while (true) {
        typeText("Choose your character:\n", 10);
        typeText("  1. Thorfinn\n", 10);
        typeText("  2. Musashi\n", 10);
        typeText("\nEnter choice (1-2): ", 10);

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            typeText("\nInvalid input. Please enter 1 or 2.\n\n", 10);
            continue;
        }

        if (choice == 1 || choice == 2) break;

        typeText("\nPlease enter 1 or 2.\n\n", 10);
    }

    cout << "\n";
    return choice;
}

// -----------------------------------------------------------------------------
// MAIN
// -----------------------------------------------------------------------------
int main() {
    // Core game systems
    Inventory inv;
    AttackHistory history;
    Shop shop;

    // Walls
    Wall1 wall1;
    Wall2 wall2;
    // Wall3 wall3; // uncomment if you want to use it later

    Player* hero = nullptr;

    // Intro + character selection
    showIntro();
    int choice = askCharacterChoice();

    if (choice == 1) {
        hero = new Thorfinn("Thorfinn", 200, 100, 0);
        typeText("You have chosen Thorfinn, the relentless storm of steel.\n\n", 20);
    } else {
        hero = new Musashi("Musashi", 200, 100, 0);
        typeText("You have chosen Musashi, the silent blade of the void.\n\n", 20);
    }

    typeText("Your journey into the Galactic Graveyard begins...\n\n", 25);

    // =========================
    //      GAME PROGRESSION
    // =========================

    // Shop before Wall 1
    typeText("Before you breach the first wall of wreckage, you dock with a supply drone.\n", 20);
    typeText("Time to prepare your loadout.\n\n", 20);
    shop.open(inv);

    // WALL 1
    if (!wall1.run(*hero, inv, history)) {
        typeText("\nYour legend ends at the first wall of the Graveyard.\n", 25);
        delete hero;
        return 0;
    }

    // Transition to Wall 2
    typeText("\nThe debris field behind you falls silent.\n", 25);
    typeText("Ahead, a second barrier of twisted hulls and hostile signals flickers into view.\n", 25);
    typeText("You reroute power, recalibrate your weapons, and steel yourself for the next assault.\n\n", 25);

    // Shop before Wall 2
    typeText("A roaming merchant vessel latches onto your airlock. Another chance to rearm.\n\n", 20);
    shop.open(inv);

    // WALL 2
    if (!wall2.run(*hero, inv, history)) {
        typeText("\nThe second wall of the Graveyard claims another hunter.\n", 25);
        delete hero;
        return 0;
    }

    // If you add Wall 3 later:
    /*
    typeText("\nBeyond the second wall lies a region of absolute darkness.\n", 25);
    typeText("Sensors fail, and only the echoes of distant engines guide your approach.\n\n", 25);
    typeText("One last chance to prepare before the final gauntlet.\n\n", 25);
    shop.open(inv);

    if (!wall3.run(*hero, inv, history)) {
        typeText("\nThe abyssal gate closes behind your shattered hull.\n", 25);
        delete hero;
        return 0;
    }
    */

    // -------------------------------------------------------------------------
    // Victory outro
    // -------------------------------------------------------------------------
    cout << "\n=================================================\n\n";
    typeText("Against all odds, you conquered the Galactic Graveyard.\n", 30);
    typeText("Your name will be whispered across the stars,\n", 30);
    typeText("echoing through the wreckage of a thousand fallen fleets.\n\n", 30);
    cout << "=================================================\n\n";

    delete hero;
    return 0;
}
