
#pragma once

struct Stats {
    int hp;
    int attack;
    int defense;
    int spAttack;
    int spDefense;
    int speed;
};

enum class Nature {
    HARDY,
    ADAMANT,
    MODEST,
    JOLLY,
    BOLD
};

enum class StatType {
    HP,
    ATTACK,
    DEFENSE,
    SP_ATTACK,
    SP_DEFENSE,
    SPEED
};

// Function declarations
double getNatureMultiplier(Nature nature, StatType stat);

int calculate_HP(int baseHP, int hpIV, int hpEV, int level);

int calculate_NON_HP(
    int baseStat,
    int IV,
    int EV,
    int level,
    double natureMultiplier
);

Stats calculateStats(
    const Stats& baseStats,
    const Stats& ivs,
    const Stats& evs,
    int level,
    Nature nature
);
