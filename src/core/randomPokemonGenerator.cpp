#include <string>
#include <iostream>
#include <vector>
#include "randomPokemonGenerator.h"
#include <random>
#include "moves.h"

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
    // Implementation for generating learned moves
    std::vector<std::string> learnedMoves;
    // Add logic here to generate learned moves based on species and level
    const auto& learnableMoves = species.learnableMoves;

    //find the highest level move that the pokemon can learn
    for (const auto& move : learnableMoves) {
        if (move.level <= level && learnedMoves.size() < 4) {
            learnedMoves.push_back(move.moveID);
        }
    }

    return learnedMoves;
}