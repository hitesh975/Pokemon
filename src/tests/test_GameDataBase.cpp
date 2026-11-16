
#include <iostream>
#include <cassert>
#include <stdexcept>
#include "gameDataBase.h"

int main() {

    // Initialize database
    GameDataBase database;

    // Test Pokémon retrieval
    const PokemonSpecies& cindercub = database.getPokemon("001");
    assert(cindercub.name == "Cindercub");

    // Test move retrieval
    const Move& ember = database.getMove("ember");
    assert(ember.name == "Ember");

    // Test invalid move ID
    try {
        database.getMove("fake_move");
        assert(false);
    }
    catch (const std::runtime_error&) {
        std::cout << "Invalid move ID handled correctly!\n";
    }

    std::cout << "All GameDatabase tests passed!\n";

    return 0;
}
