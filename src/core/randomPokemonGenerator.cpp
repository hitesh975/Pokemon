#include <string>
#include <iostream>
#include <vector>
#include "randomPokemonGenerator.h"
#include <random>
#include "moves.h"
#include "stats.h"

using namespace std;

pokemonGenerator::pokemonGenerator(const GameDataBase& database)
    : database(database), randomEngine(std::random_device{}()) {
}

Pokemon pokemonGenerator::generateRandomPokemon(const vector<PokemonSpecies>& pokemonList) {
    
    //random species selection
    const PokemonSpecies& randomSpecies = pokemonList[randomEngine() % pokemonList.size()];

    //random IVs generation
    Stats ivs = generateIVs();

    //random nature generation
    Nature nature = generateNature();

    //random level generation
    int level = generateLevel();


    //random moves generation
    std::vector<std::string> learnedMoves = generateLearnedMoves(randomSpecies, level);

    //base stats
    const Stats &baseStats = getBaseStats(randomSpecies.id);

    //calculated stats
    const Stats evs = {0, 0, 0, 0, 0, 0};
    const Stats calculatedStats = calculateStats(baseStats, ivs, evs, level, nature);

    //assemble everything
    Pokemon pokemon;

    pokemon.speciesID = randomSpecies.id;
    pokemon.level = level;
    pokemon.experience = 0;
    pokemon.friendship = 50;
    pokemon.nature = nature;
    pokemon.ivs = ivs;
    pokemon.evs = evs;
    pokemon.calculatedStats = calculatedStats;
    pokemon.learnedMoves = learnedMoves;

    return pokemon;
}


//generate random IVs
Stats pokemonGenerator::generateIVs() {
    std::uniform_int_distribution<int> distribution(0, 31);

    //HP IV
    const int hpIV = distribution(randomEngine);

    const int attackIV = distribution(randomEngine);

    const int defenceIV = distribution(randomEngine);

    const int specialAttackIV = distribution(randomEngine);

    const int specialDefenceIV = distribution(randomEngine);

    const int speedIV = distribution(randomEngine);

    return {
        hpIV,
        attackIV,
        defenceIV,
        specialAttackIV,
        specialDefenceIV,
        speedIV
    };
}

//generate random nature
Nature pokemonGenerator::generateNature() {
    std::uniform_int_distribution<int> distribution(0, 4);

    int randomIndex = distribution(randomEngine);

    return static_cast<Nature>(randomIndex);
}


//random level generator
int pokemonGenerator::generateLevel() {
    std::uniform_int_distribution<int> distribution(0, 100);
    int level = distribution(randomEngine);
    return level;
}

std::vector<std::string> pokemonGenerator::generateLearnedMoves(const PokemonSpecies& species, int level) {
    std::vector<std::string> learnedMoves;
    const auto& learnableMoves = species.learnableMoves;

    for (const auto& move : learnableMoves) {
        if (move.level <= level) {
            learnedMoves.push_back(move.moveID);
        }
    }

    if (learnedMoves.size() > 4) {
        learnedMoves.erase(learnedMoves.begin(), learnedMoves.end() - 4);
    }

    return learnedMoves;
}

//get base stats
const Stats& pokemonGenerator::getBaseStats(
    const std::string& speciesID) const {

        const auto& species = database.getPokemon(speciesID);
        return species.baseStats;
    }


//calculate stats

Stats pokemonGenerator::calculateStats(
    const Stats& baseStats,
    const Stats& ivs,
    const Stats& evs,
    int level,
    Nature nature
) {

    return ::calculateStats(baseStats, ivs, evs, level, nature);
}