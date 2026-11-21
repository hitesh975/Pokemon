#include "moves.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <stdexcept>
#include <unordered_map>
#include <string>
#include <vector>

#include "loadmoves.h"

using json = nlohmann::json;

std::unordered_map<std::string, Move> loadMoves(const std::string& filePath) {
    const std::vector<std::string> candidatePaths = {
        filePath,
        "dataset/moves.JSON",
        "dataset/moves.json"
    };

    std::ifstream file;
    bool opened = false;
    for (const auto& path : candidatePaths) {
        if (path.empty()) continue;
        file.open(path);
        if (file.is_open()) {
            opened = true;
            break;
        }
    }

    if (!opened) {
        throw std::runtime_error("Could not open move dataset file");
    }

    json moveData = json::parse(file);

    std::unordered_map<std::string, Move> moves;

    for (const auto& entry : moveData["moves"]) {
        Move move;

        move.id = entry["id"].get<std::string>();
        
        move.name = entry["name"].get<std::string>();
        
        move.power = entry["power"].get<int>();
        
        move.accuracy = entry["accuracy"].get<int>();
        
        move.priority = entry["priority"].get<int>();
        
        move.pp = entry["pp"].get<int>();
        
        move.heal = entry["heal"].get<int>();

        move.effect = stringToMoveEffect(entry["effect"].get<std::string>());
        
        move.effectChance = entry["effectChance"].get<int>();

        move.volatileStatus = stringToVolatileStatus(entry["volatileStatus"].get<std::string>());

        move.volatileStatusChance = entry["volatileStatusChance"].get<int>();
        
        if (!entry["categories"].is_array()) {
            throw std::invalid_argument("Move categories must be an array: " + move.id);
        }
        for (const auto& category : entry["categories"]) {
            move.categories.push_back(stringToMoveCategory(category.get<std::string>()));
        }
        if (move.categories.empty()) {
            throw std::invalid_argument("Move must have at least one category: " + move.id);
        }
        
        move.type = stringToPokemonType(entry["type"].get<std::string>());
        
        moves[move.id] = move;
    }
    return moves;
}
