#include "moves.h"
#include <string>
#include <vector>
#pragma once

using namespace std;

// Species information
struct PokemonSpecies {
    string id;
    string name;
    vector<PokemonType> types;

    Stats baseStats;
    vector<LearnableMove> learnableMoves;
};
