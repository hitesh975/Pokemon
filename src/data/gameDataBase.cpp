#include "gameDataBase.h"
#include "loadmoves.h"
#include "loadpokemons.h"
#include <string>
#include <stdexcept>

GameDataBase::GameDataBase() {
    moves = loadMoves("dataset/moves.json");
    pokemons = loadPokemonSpeciesFromJson();
}

const Move& GameDataBase::getMove(const std::string& id) const {
    auto it = moves.find(id);
    if (it == moves.end()) {
        throw std::runtime_error("Move not found: " + id);
    }
    return it->second;
}

const PokemonSpecies& GameDataBase::getPokemon(const std::string& id) const {
    auto it = pokemons.find(id);
    if (it == pokemons.end()) {
        throw std::runtime_error("Pokemon species not found: " + id);
    }
    return it->second;
}

const std::unordered_map<std::string, PokemonSpecies>& GameDataBase::getAllPokemons() const {
    return pokemons;
}
