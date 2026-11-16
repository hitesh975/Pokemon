
#include <nlohmann/json.hpp>
#include <fstream>
#include <stdexcept>
#include <unordered_map>
#include <string>
#include <utility>

#include "pokemons.h"

using json = nlohmann::json;

std::unordered_map<std::string, PokemonSpecies> loadPokemonSpeciesFromJson() {

    std::ifstream file("pokemons.json");

    // Check whether the file opened successfully
    if (!file.is_open()) {
        throw std::runtime_error("Could not open pokemons.json");
    }

    // Parse JSON
    json pokemonData = json::parse(file);

    // Check that the species array exists
    if (!pokemonData.contains("species") || !pokemonData["species"].is_array()) {
        throw std::runtime_error("Invalid pokemons.json: missing species array");
    }

    std::unordered_map<std::string, PokemonSpecies> pokemonSpecies;

    for (const auto& entry : pokemonData["species"]) {

        PokemonSpecies species;

        species.id = entry.at("id").get<std::string>();
        species.name = entry.at("name").get<std::string>();

        // Parse types
        for (const auto& type : entry.at("types")) {
            int typeValue = type.get<int>();

            if (typeValue < 0 || typeValue >= 18) {
                throw std::runtime_error("Invalid PokemonType value in species: " + species.id);
            }

            species.types.push_back(static_cast<PokemonType>(typeValue));
        }

        // Parse base stats
        const auto& stats = entry.at("baseStats");

        species.baseStats.hp = stats.at("hp").get<int>();
        species.baseStats.attack = stats.at("attack").get<int>();
        species.baseStats.defense = stats.at("defense").get<int>();
        species.baseStats.spAttack = stats.at("spAttack").get<int>();
        species.baseStats.spDefense = stats.at("spDefense").get<int>();
        species.baseStats.speed = stats.at("speed").get<int>();

        // Parse learnable moves
        for (const auto& move : entry.at("learnableMoves")) {

            LearnableMove learnableMove;

            learnableMove.moveID = move.at("moveID").get<std::string>();
            learnableMove.level = move.at("level").get<int>();

            species.learnableMoves.push_back(std::move(learnableMove));
        }

        // Insert species and detect duplicate IDs
        auto [iterator, inserted] = pokemonSpecies.emplace(
            species.id,
            std::move(species)
        );

        if (!inserted) {
            throw std::runtime_error("Duplicate Pokemon species ID: " + iterator->first);
        }
    }

    return pokemonSpecies;
}
