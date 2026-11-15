
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <nlohmann/json.hpp>
#include "stats.h"

using namespace std;
using json = nlohmann::json;

// Move IDs
enum class MoveID {
    EMBER,
    QUICK_ATTACK,
    THUNDERBOLT,
    THUNDER_WAVE,
    RECOVER,
    SWORDS_DANCE
};

enum class MoveCategory {
    DAMAGE,
    STATUS,
    HEAL,
    STAT_CHANGE
};

//learnable moves by a pokemon specie
struct LearnableMove {
    string moveID;
    int level;
};

// Pokemon types
enum class PokemonType {
    FIRE,
    WATER,
    GRASS,
    ELECTRIC,
    NORMAL,
    FLYING,
    PSYCHIC,
    GROUND,
    ROCK,
    ICE,
    BUG,
    POISON,
    FIGHTING,
    GHOST,
    DRAGON,
    DARK,
    STEEL,
    FAIRY
};

// Move information
struct Move {
    string id;
    string name;
    MoveCategory category;
    PokemonType type;

    int power;
    int accuracy;
    int pp;

    string effect;
    int effectChance;
};

// Species information
struct PokemonSpecies {
    string id;
    string name;
    vector<PokemonType> types;

    Stats baseStats;
    vector<LearnableMove> learnableMoves;
};

// Individual Pokemon
struct Pokemon {
    string speciesID;

    int level;
    int experience;
    int friendship;

    Nature nature;

    Stats ivs;
    Stats evs;

    array<MoveID, 4> learnedMoves;
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