#include "moves.h"

// Species information
struct PokemonSpecies {
    string id;
    string name;
    vector<PokemonType> types;

    Stats baseStats;
    vector<LearnableMove> learnableMoves;
};