
#include <nlohmann/json.hpp>
#include <fstream>
#include <stdexcept>
#include <unordered_map>
#include <string>
#include <utility>

#include "pokemons.h"

using json = nlohmann::json;

PokemonType stringToPokemonType(const std::string& typeStr) {
    if (typeStr == "FIRE") return PokemonType::FIRE;
    else if (typeStr == "WATER") return PokemonType::WATER;
    else if (typeStr == "GRASS") return PokemonType::GRASS;
    else if (typeStr == "ELECTRIC") return PokemonType::ELECTRIC;
    else if (typeStr == "NORMAL") return PokemonType::NORMAL;
    else if (typeStr == "FLYING") return PokemonType::FLYING;
    else if (typeStr == "PSYCHIC") return PokemonType::PSYCHIC;
    else if (typeStr == "GROUND") return PokemonType::GROUND;
    else if (typeStr == "ROCK") return PokemonType::ROCK;
    else if (typeStr == "ICE") return PokemonType::ICE;
    else if (typeStr == "BUG") return PokemonType::BUG;
    else if (typeStr == "POISON") return PokemonType::POISON;
    else if (typeStr == "FIGHTING") return PokemonType::FIGHTING;
    else if (typeStr == "GHOST") return PokemonType::GHOST;
    else if (typeStr == "DRAGON") return PokemonType::DRAGON;
    else if (typeStr == "DARK") return PokemonType::DARK;
    else if (typeStr == "STEEL") return PokemonType::STEEL;
    else if (typeStr == "FAIRY") return PokemonType::FAIRY;

    throw std::invalid_argument("Invalid Pokemon type: " + typeStr);
}

std::unordered_map<std::string, PokemonSpecies> loadPokemonSpeciesFromJson() {

    std::ifstream file("dataset/pokemons.json");

    if (!file.is_open()) {
        throw std::runtime_error("Could not open dataset/pokemons.json");
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
