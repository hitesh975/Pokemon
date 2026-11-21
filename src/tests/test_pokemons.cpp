
#include <iostream>
#include <cassert>
#include <algorithm>
#include "pokemons.h"
#include "loadmoves.h"
#include "loadpokemons.h"

int main() {

    // Load species from JSON
    auto pokemonSpecies = loadPokemonSpeciesFromJson();

    // Test 1: Check number of species
    assert(pokemonSpecies.size() == 9);

    // Test 2: Retrieve Cindercub
    const auto& cindercub = pokemonSpecies.at("001");

    // Test 3: Check basic information
    assert(cindercub.name == "Cindercub");

    // Test 4: Check types
    assert(cindercub.types.size() == 1);

    // Test 5: Check base stats
    assert(cindercub.baseStats.hp == 45);
    assert(cindercub.baseStats.attack == 55);
    assert(cindercub.baseStats.defense == 40);

    // Test 6: Check learnable moves
    assert(!cindercub.learnableMoves.empty());
    assert(cindercub.learnableMoves[0].moveID == "tackle");

    const auto moves = loadMoves("dataset/moves.JSON");
    const auto hasCategory = [](const Move& move, MoveCategory category) {
        return std::find(move.categories.begin(), move.categories.end(), category) != move.categories.end();
    };
    assert(hasCategory(moves.at("tackle"), MoveCategory::PHYSICAL));
    assert(!hasCategory(moves.at("tackle"), MoveCategory::SPECIAL));
    assert(hasCategory(moves.at("ember"), MoveCategory::SPECIAL));
    assert(hasCategory(moves.at("ember"), MoveCategory::STATUS));
    assert(hasCategory(moves.at("psychic"), MoveCategory::SPECIAL));
    assert(hasCategory(moves.at("psychic"), MoveCategory::STAT_CHANGE));

    std::cout << "All Pokemon loader tests passed!\n";

    return 0;
}
