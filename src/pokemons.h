#pragma once

#include <string>
#include <vector>
#include <unordered_map>

// Species information
struct PokemonSpecies {
    std::string id;
    std::string name;
    std::vector<PokemonType> types;

    Stats baseStats;
    std::vector<LearnableMove> learnableMoves;
};

std::unordered_map<std::string, PokemonSpecies> loadPokemonSpeciesFromJson();
