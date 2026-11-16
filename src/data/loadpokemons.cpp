
#include <nlohmann/json.hpp>
#include <fstream>
#include <stdexcept>
#include <unordered_map>
#include <string>
#include <utility>
#include <vector>
#include "stats.h"
#include "moves.h"
#include "loadpokemons.h"


#include "pokemons.h"

using json = nlohmann::json;

std::unordered_map<std::string, PokemonSpecies> loadPokemonSpeciesFromJson() {

    const std::vector<std::string> candidatePaths = {
        "dataset/pokemons.JSON",
        "dataset/pokemons.json"
    };

    std::ifstream file;
    bool opened = false;
    for (const auto& path : candidatePaths) {
        file.open(path);
        if (file.is_open()) {
            opened = true;
            break;
        }
    }

    if (!opened) {
        throw std::runtime_error("Could not open pokemon dataset file");
    }

    json pokemonData = json::parse(file);

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
            species.types.push_back(
                stringToPokemonType(type.get<std::string>())
            );
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
