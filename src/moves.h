#include <string>
#pragma once

enum class MoveCategory {
    DAMAGE,
    STATUS,
    HEAL,
    STAT_CHANGE
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

//learnable moves by a pokemon specie
struct LearnableMove {
    std::string moveID;
    int level;
};

// Move information
struct Move {
    std::string id;
    std::string name;
    MoveCategory category;
    PokemonType type;

    int power;
    int accuracy;
    int pp;

    std::string effect;
    int effectChance;
};

struct Stats {
    int hp;
    int attack;
    int defense;
    int spAttack;
    int spDefense;
    int speed;
};

