#include <cassert>
#include <string>
#include <vector>

#include "gameDataBase.h"
#include "randomPokemonGenerator.h"

int main() {
    GameDataBase database;
    pokemonGenerator generator(database);

    PokemonSpecies species = database.getPokemon("001");
    species.learnableMoves = {
        {"move1", -1},
        {"move2", -1},
        {"move3", -1},
        {"move4", -1},
        {"move5", -1},
        {"move6", -1}
    };

    const Pokemon generated = generator.generateRandomPokemon({species});
    assert((generated.learnedMoves == std::vector<std::string>{
        "move3", "move4", "move5", "move6"
    }));

    const Stats expectedStats = calculateStats(
        species.baseStats,
        generated.ivs,
        generated.evs,
        generated.level,
        generated.nature
    );
    assert(generated.calculatedStats.hp == expectedStats.hp);
    assert(generated.calculatedStats.attack == expectedStats.attack);
    assert(generated.calculatedStats.defense == expectedStats.defense);
    assert(generated.calculatedStats.spAttack == expectedStats.spAttack);
    assert(generated.calculatedStats.spDefense == expectedStats.spDefense);
    assert(generated.calculatedStats.speed == expectedStats.speed);

    species.learnableMoves = {
        {"early1", -1},
        {"unavailable", 101},
        {"early2", -1}
    };
    const Pokemon withFewerMoves = generator.generateRandomPokemon({species});
    assert((withFewerMoves.learnedMoves == std::vector<std::string>{
        "early1", "early2"
    }));

    species.learnableMoves = {
        {"unavailable1", 101},
        {"unavailable2", 101}
    };
    const Pokemon withNoMoves = generator.generateRandomPokemon({species});
    assert(withNoMoves.learnedMoves.empty());

    return 0;
}
