#pragma once

#include <stdexcept>
#include <string>
#include <vector>

enum class MoveCategory {
    PHYSICAL,
    SPECIAL,
    STATUS,
    HEAL
};

enum class MoveEffect {
    NONE,
    BURN,
    PARALYZE,
    SLEEP,
    FREEZE,
    POISON
};

enum class VolatileStatus {
    //enemy pokemons
    NONE,
    CONFUSION,
    DROWSY,
    BIND, //4-5 turns
    CANT_ESCAPE,
    CURSED,
    EMBARGO, //cannot use held item for 5 turns
    ENCORE,
    FLINCH,
    FUTURE_ATTACK,
    IDENTIFIED,
    LEECH_SEED, //skull emoji
    LOCKED_ON,
    MOVE_DISABLED,
    NIGHTMARE,
    TAUNTED,

    //opposite side
    SPIKES,
    STEALTH_ROCK,
    TOXIC_SPIKES,
    STICKY_WEBS,

    //user
    CHARGING,
    CRITICAL_HIT_RATIO_BOOST,
    DESTINY_BOUND,
    ELECTRIC_BOOST,
    FLASH_FIRE,
    INGRAINED, //skul emoji
    LASER_FOCUS,
    MINIMIZED,
    RAMPAGING,
    RECHARGING,
    SEALING_OFF,
    SKY_HIGH,
    STOCKPILING,
    SUBMERGED,
    UNDERGROUND,
    UPROAR,

    //user side
    LIGHT_SCREEN,
    AURORA_VIEL,
    REFLECT,
    SAFEGUARD,
    TAILWIND,

    //all pokemon
    FAIRY_LOCKED,
    JAW_LOCK,
    TRICK_ROOM,
    WONDER_ROOM,

    //status that dont change til withdrawn

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
    if (categoryStr == "PHYSICAL") {
        return MoveCategory::PHYSICAL;
    } else if (categoryStr == "SPECIAL") {
        return MoveCategory::SPECIAL;
    } else if (categoryStr == "STATUS") {
        return MoveCategory::STATUS;
    } else if (categoryStr == "HEAL") {
        return MoveCategory::HEAL;
    }

    throw std::invalid_argument("Invalid move category: " + categoryStr);
}

inline MoveEffect stringToMoveEffect(const std::string& effectStr) {
    if (effectStr == "NONE") return MoveEffect::NONE;
    else if (effectStr == "BURN") return MoveEffect::BURN;
    else if (effectStr == "PARALYZE") return MoveEffect::PARALYZE;
    else if (effectStr == "SLEEP") return MoveEffect::SLEEP;
    else if (effectStr == "POISON") return MoveEffect::POISON;
    else if (effectStr == "FREEZE") return MoveEffect::FREEZE;

    throw std::invalid_argument("Invalid move effect: " + effectStr);
}

inline VolatileStatus stringToVolatileStatus(const std::string& statusStr) {
    if (statusStr == "NONE") return VolatileStatus::NONE;
    else if (statusStr == "CONFUSION") return VolatileStatus::CONFUSION;
    else if (statusStr == "DROWSY") return VolatileStatus::DROWSY;

    throw std::invalid_argument("Invalid volatile status: " + statusStr);
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
    std::vector<MoveCategory> categories;
    PokemonType type;

    int power;
    int accuracy;
    int priority;
    int pp;

    int heal;
    MoveEffect effect;
    int effectChance;
    VolatileStatus volatileStatus;
    int volatileStatusChance;
};


