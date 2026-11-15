#include <iostream>
#include "stats.h"

using namespace std;

int main() {
    // Sample Pokémon base stats
    Stats baseStats = {45, 55, 40, 65, 45, 65};

    // Sample IVs
    Stats ivs = {20, 15, 10, 25, 12, 30};

    // Sample EVs
    Stats evs = {0, 0, 0, 0, 0, 0};

    int level = 5;
    Nature nature = Nature::ADAMANT;

    // Call your calculator
    Stats result = calculateStats(baseStats, ivs, evs, level, nature);

    // Print results
    cout << "HP: " << result.hp << endl;
    cout << "Attack: " << result.attack << endl;
    cout << "Defense: " << result.defense << endl;
    cout << "Sp. Attack: " << result.spAttack << endl;
    cout << "Sp. Defense: " << result.spDefense << endl;
    cout << "Speed: " << result.speed << endl;

    return 0;
}