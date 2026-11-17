// Individual Pokemon
#include <string>
#include <array>
#include "stats.h"
#include <vector>
#include "pokemons.h"
#include "./data/gameDataBase.h"
#include <random>
using namespace std;

struct Pokemon {
    string speciesID;

    int level;
    int experience;
    int friendship;

    Nature nature;

    Stats ivs;
    Stats evs;

    array<string, 4> learnedMoves;
};

class pokemonGenerator {
    public:
        pokemonGenerator(const GameDataBase& database);
        Pokemon generateRandomPokemon(const vector<PokemonSpecies>& pokemonList);

    private:
        const GameDataBase& database;
        std::mt19937 randomEngine;

        Stats generateIVs();
        Nature generateNature();
        int generateLevel();


        std::vector<std::string> generateLearnedMoves(
        const PokemonSpecies& species,
        int level
    );
};

