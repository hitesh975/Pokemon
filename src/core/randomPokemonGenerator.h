// Individual Pokemon
#include <string>
#include "stats.h"
#include <vector>
#include "pokemons.h"
#include "../data/gameDataBase.h"
#include <random>
using namespace std;

struct PokemonMove {
    std::string moveID;
    int currentPP;
};

struct Pokemon {
    string speciesID;
    vector<PokemonType> types;

    int level;
    int experience;
    int friendship;

    Nature nature;

    Stats ivs;
    Stats evs;
    Stats calculatedStats;
    int currentHP;

    vector<PokemonMove> learnedMoves;
};

class pokemonGenerator {
    public:
        pokemonGenerator(const GameDataBase& database);
        Pokemon generateRandomPokemon(
        const std::vector<const PokemonSpecies*>& pokemonList);

    private:
        const GameDataBase& database;
        std::mt19937 randomEngine;

        Stats generateIVs();
        Nature generateNature();
        int generateLevel();


        std::vector<PokemonMove> generateLearnedMoves(
        const PokemonSpecies& species,
        int level
        );

        const Stats& getBaseStats(const std::string& speciesID) const;

        Stats calculateStats(const Stats& baseStats, const Stats& ivs, const Stats& evs, int level, Nature nature);

};

