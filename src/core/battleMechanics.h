#pragma once

#include "../data/gameDataBase.h"
#include "randomPokemonGenerator.h"
#include <vector>

enum class TurnOrder {
    FIRST_POKEMON,
    SECOND_POKEMON
};

class TextBasedBattle {
public:
    TextBasedBattle();
    void startBattle();

    TurnOrder determineTurnOrder(
        const Pokemon& p1,
        const Pokemon& p2,
        const Move& m1,
        const Move& m2
    ) const;

    int calculateDamage(
        const Pokemon& attacker,
        const Pokemon& defender,
        const Move& move
    ) const;

    double GetSTAB(const Pokemon& pokemon, const Move& move) const;

    double TypeEffectivenessCalculator(
        const Move& move,
        const Pokemon& defender
    ) const;

    double getCrit() const;
    int GetRandomDamageModifier() const;

private:
    GameDataBase database;
    std::vector<const PokemonSpecies*> PokemonList;
    Pokemon pokemon1;
    Pokemon pokemon2;
};