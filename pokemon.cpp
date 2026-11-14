
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;


// ==========================================
// ENUMS
// ==========================================

// Unique identifiers for moves
enum class MoveID {
    THUNDERBOLT,
    THUNDER_WAVE,
    RECOVER,
    SWORDS_DANCE
};

// Move categories
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

// Nature
enum class Nature {
    HARDY,
    ADAMANT,
    MODEST,
    JOLLY,
    BOLD
};


// ==========================================
// STAT STRUCTURE
// ==========================================

struct Stats {
    int hp;
    int attack;
    int defense;
    int spAttack;
    int spDefense;
    int speed;
};


// ==========================================
// MOVE STRUCTURE
// ==========================================

struct Move {
    string name;
    MoveCategory category;
    PokemonType type;

    int power;
    int accuracy;
    int pp;
};


// ==========================================
// POKEMON SPECIES DATA
// ==========================================

struct PokemonSpecies {
    string name;
    PokemonType type;
    
    Stats baseStats;
};


// ==========================================
// INDIVIDUAL POKEMON DATA
// ==========================================

struct Pokemon {
    string nickname;
    int level;
    int experience;

    int friendship;
    Nature nature;

    // Individual values
    Stats ivs;

    // Effort values
    Stats evs;

    // References to the central move database
    array<MoveID, 4> learnedMoves;
};


// ==========================================
// BATTLE STATE
// ==========================================

struct BattleState {
    int currentHP;

    // Temporary stat modifications during battle
    int attackStage = 0;
    int defenseStage = 0;
    int spAttackStage = 0;
    int spDefenseStage = 0;
    int speedStage = 0;
};


// ==========================================
// MAIN
// ==========================================

int main() {

    return 0;
}
