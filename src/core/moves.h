#pragma once

#include <stdexcept>
#include <string>

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

inline MoveCategory stringToMoveCategory(const std::string& categoryStr) {
    if (categoryStr == "DAMAGE" || categoryStr == "PHYSICAL" || categoryStr == "SPECIAL") {
        return MoveCategory::DAMAGE;
    } else if (categoryStr == "STATUS") {
        return MoveCategory::STATUS;
    } else if (categoryStr == "HEAL") {
        return MoveCategory::HEAL;
    } else if (categoryStr == "STAT_CHANGE") {
        return MoveCategory::STAT_CHANGE;
    }

    throw std::invalid_argument("Invalid move category: " + categoryStr);
}

inline PokemonType stringToPokemonType(const std::string& typeStr) {
    if (typeStr == "FIRE") return PokemonType::FIRE;
    else if (typeStr == "WATER") return PokemonType::WATER;
    else if (typeStr == "GRASS") return PokemonType::GRASS;
    else if (typeStr == "ELECTRIC") return PokemonType::ELECTRIC;
    else if (typeStr == "NORMAL") return PokemonType::NORMAL;
    else if (typeStr == "FLYING") return PokemonType::FLYING;
    else if (typeStr == "PSYCHIC") return PokemonType::PSYCHIC;
    else if (typeStr == "GROUND") return PokemonType::GROUND;
    else if (typeStr == "ROCK") return PokemonType::ROCK;
    else if (typeStr == "ICE") return PokemonType::ICE;
    else if (typeStr == "BUG") return PokemonType::BUG;
    else if (typeStr == "POISON") return PokemonType::POISON;
    else if (typeStr == "FIGHTING") return PokemonType::FIGHTING;
    else if (typeStr == "GHOST") return PokemonType::GHOST;
    else if (typeStr == "DRAGON") return PokemonType::DRAGON;
    else if (typeStr == "DARK") return PokemonType::DARK;
    else if (typeStr == "STEEL") return PokemonType::STEEL;
    else if (typeStr == "FAIRY") return PokemonType::FAIRY;

    throw std::invalid_argument("Invalid Pokemon type: " + typeStr);
}

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

