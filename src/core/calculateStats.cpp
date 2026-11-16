//Accepts a base stat.
//Accepts an IV.
//Accepts an EV.
//Accepts a level.

#include "stats.h"

//helper functions

//get nature multiplier
double getNatureMultiplier(Nature nature, StatType stat) {

    switch (nature) {

        case Nature::HARDY:
            return 1.0;

        case Nature::ADAMANT:
            if (stat == StatType::ATTACK) return 1.1;
            if (stat == StatType::SP_ATTACK) return 0.9;
            break;

        case Nature::MODEST:
            if (stat == StatType::SP_ATTACK) return 1.1;
            if (stat == StatType::ATTACK) return 0.9;
            break;

        case Nature::JOLLY:
            if (stat == StatType::SPEED) return 1.1;
            if (stat == StatType::SP_ATTACK) return 0.9;
            break;

        case Nature::BOLD:
            if (stat == StatType::DEFENSE) return 1.1;
            if (stat == StatType::ATTACK) return 0.9;
            break;
    }

    return 1.0;
}


//hp function
int calculate_HP(
    int baseHP,
    int HPIV,
    int HPEV,
    int level
){
    const int hp = ((2 * baseHP + HPIV + (HPEV / 4)) * level) / 100 + level + 10;
    return hp;
}


//non-hp function
int calculate_NON_HP(
    int baseStat,
    int IV,
    int EV,
    int level,
    double natureMultiplier
) {
    double stat = (
        ((2 * baseStat + IV + (EV / 4)) * level) / 100.0 + 5
    ) * natureMultiplier;

    return static_cast<int>(stat);
}


////////////main function ////////////

Stats calculateStats(
    const Stats& baseStats,
    const Stats& ivs,
    const Stats& evs,
    int level,
    Nature nature
) {

    //calculate HP
    int hp = calculate_HP(baseStats.hp, ivs.hp, evs.hp, level);

    //calculate other stats
    double natureMultiplier = getNatureMultiplier(nature, StatType::ATTACK);
    int attack = calculate_NON_HP(baseStats.attack, ivs.attack, evs.attack, level, natureMultiplier);

    natureMultiplier = getNatureMultiplier(nature, StatType::DEFENSE);
    int defense = calculate_NON_HP(baseStats.defense, ivs.defense, evs.defense, level, natureMultiplier);

    natureMultiplier = getNatureMultiplier(nature, StatType::SP_ATTACK);
    int spAttack = calculate_NON_HP(baseStats.spAttack, ivs.spAttack, evs.spAttack, level, natureMultiplier);

    natureMultiplier = getNatureMultiplier(nature, StatType::SP_DEFENSE);
    int spDefense = calculate_NON_HP(baseStats.spDefense, ivs.spDefense, evs.spDefense, level, natureMultiplier);

    natureMultiplier = getNatureMultiplier(nature, StatType::SPEED);
    int speed = calculate_NON_HP(baseStats.speed, ivs.speed, evs.speed, level, natureMultiplier);


    Stats result;
    result.hp = hp;
    result.attack = attack;
    result.defense = defense;
    result.spAttack = spAttack;
    result.spDefense = spDefense;
    result.speed = speed;

    return result;
}