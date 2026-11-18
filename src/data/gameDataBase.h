#pragma once
#include "moves.h"
#include "pokemons.h"
#include <unordered_map>
#include <string>

class GameDataBase {
    public:
        GameDataBase();
        const Move& getMove(const std::string& id) const;

        const PokemonSpecies& getPokemon(const std::string& id) const;

        const std::unordered_map<std::string, PokemonSpecies>& getAllPokemons() const;

    private:
        std::unordered_map<std::string, Move> moves;

        std::unordered_map<std::string, PokemonSpecies> pokemons;
};