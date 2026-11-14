
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;


// Move IDs
enum class MoveID {
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


// Pokemon types
enum class PokemonType {
    ELECTRIC,
    FIRE,
    WATER,
    GRASS,
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

enum class Nature {
    HARDY,
    ADAMANT,
    MODEST,
    JOLLY,
    BOLD
};


// All six Pokemon stats
struct Stats {
    int hp;
    int attack;
    int defense;
    int spAttack;
    int spDefense;
    int speed;
};


// Move information
struct Move {
    string name;
    MoveCategory category;
    PokemonType type;

    int power;
    int accuracy;
    int pp;
};


// Base information for each Pokemon species
struct PokemonSpecies {
    string name;
    PokemonType type;

    Stats baseStats;
};


// An individual Pokemon
struct Pokemon {
    string nickname;
    string speciesID;

    int level;
    int experience;
    int friendship;

    Nature nature;

    Stats ivs;
    Stats evs;

    array<MoveID, 4> learnedMoves;
};


// Stats that can change during battle
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
