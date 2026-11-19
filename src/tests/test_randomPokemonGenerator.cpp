#include <cassert>
#include <vector>

#include "randomPokemonGenerator.h"

int main() {
    GameDataBase database;
    const PokemonSpecies& species = database.getPokemon("001");
    const std::vector<const PokemonSpecies*> pokemonList = {&species};

    pokemonGenerator generator(database);
    const Pokemon pokemon = generator.generateRandomPokemon(pokemonList);

    assert(pokemon.types == species.types);
}
