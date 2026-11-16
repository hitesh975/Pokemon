#pragma once

#include "pokemons.h"
#include <unordered_map>
#include <string>

std::unordered_map<std::string, PokemonSpecies> loadPokemonSpeciesFromJson();       