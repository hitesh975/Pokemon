#include "moves.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <stdexcept>
#include "loadmoves.h"
#include <unordered_map>
#include <string>

using json = nlohmann::json;

MoveCategory stringToMoveCategory(const std::string& categoryStr) {
    if (categoryStr == "DAMAGE") {
        return MoveCategory::DAMAGE;
    } else if (categoryStr == "STATUS") {
        return MoveCategory::STATUS;
    } else if (categoryStr == "HEAL") {
        return MoveCategory::HEAL;
    } else if (categoryStr == "STAT_CHANGE") {
        return MoveCategory::STAT_CHANGE;
    } else {
        throw std::invalid_argument("Invalid move category: " + categoryStr);
    }
}

PokemonType stringToPokemonType(const std::string& typeStr) {
    if (typeStr == "FIRE") {
        return PokemonType::FIRE;
    } else if (typeStr == "WATER") {
        return PokemonType::WATER;
    } else if (typeStr == "GRASS") {
        return PokemonType::GRASS;
    } else if (typeStr == "ELECTRIC") {
        return PokemonType::ELECTRIC;
    } else if (typeStr == "NORMAL") {
        return PokemonType::NORMAL;
    } else if (typeStr == "FLYING") {
        return PokemonType::FLYING;
    } else if (typeStr == "PSYCHIC") {
        return PokemonType::PSYCHIC;
    } else if (typeStr == "GROUND") {
        return PokemonType::GROUND;
    } else if (typeStr == "ROCK") {
        return PokemonType::ROCK;
    } else if (typeStr == "ICE") {
        return PokemonType::ICE;
    } else if (typeStr == "BUG") {
        return PokemonType::BUG;
    } else if (typeStr == "POISON") {
        return PokemonType::POISON;
    } else if (typeStr == "FIGHTING") {
        return PokemonType::FIGHTING;
    } else if (typeStr == "GHOST") {
        return PokemonType::GHOST;
    } else if (typeStr == "DRAGON") {
        return PokemonType::DRAGON;
    } else if (typeStr == "DARK") {
        return PokemonType::DARK;
    } else if (typeStr == "STEEL") {
        return PokemonType::STEEL;
    } else if (typeStr == "FAIRY") {
        return PokemonType::FAIRY;
    } else {
        throw std::invalid_argument("Invalid Pokémon type: " + typeStr);
    }
}

std::unordered_map<std::string, Move> loadMoves() {
    std::ifstream file("dataset/moves.json");

    json moveData = json::parse(file);

    std::unordered_map<std::string, Move> moves;

    for (const auto& entry: moveData["moves"] ) {
        Move move;
        move.id = entry["id"].get<std::string>();
        move.name = entry["name"].get<std::string>();
        move.power = entry["power"].get<int>();
        move.accuracy = entry["accuracy"].get<int>();
        move.pp = entry["pp"].get<int>();
        move.effect = entry["effect"].get<std::string>();
        move.effectChance = entry["effectChance"].get<int>();
        move.category = stringToMoveCategory(entry["category"].get<std::string>());
        move.type = stringToPokemonType(entry["type"].get<std::string>());
        moves[move.id] = move;
    }
    return moves;
}
