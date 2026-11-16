
#include <iostream>
#include <string>
#include <array>
#include <nlohmann/json.hpp>
#include "stats.h"

using namespace std;
using json = nlohmann::json;


// Individual Pokemon
struct Pokemon {
    string speciesID;

    int level;
    int experience;
    int friendship;

    Nature nature;

    Stats ivs;
    Stats evs;

    array<string, 4> learnedMoves;
};

// Battle information
struct BattleState {
    int currentHP;

    int attackStage = 0;
    int defenseStage = 0;
    int spAttackStage = 0;
    int spDefenseStage = 0;
    int speedStage = 0;
};

int main() {

    return 0;
}