#include "battleMechanics.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <stdexcept>
#include <random>
using namespace std;


///////////////////   NOTE   /////////////////////

    //NEED TO ADD:
        //damage calc
        //move categories resolver

        // goodluck _||_ im sleeping 


TextBasedBattle::TextBasedBattle() {
    pokemonGenerator generator(database);

    for (const auto& [id, species] : database.getAllPokemons()) {
        (void)id;
        PokemonList.push_back(&species);
    }

    if (PokemonList.empty()) {
        throw runtime_error("Cannot create a battle without Pokemon");
    }

    pokemon1 = generator.generateRandomPokemon(PokemonList);
    pokemon2 = generator.generateRandomPokemon(PokemonList);
}


//determine turn order
TurnOrder determineTurnOrder(
    const Pokemon& p1,
    const Pokemon& p2,
    const Move& m1,
    const Move& m2
) {
    if (m1.priority > m2.priority) {
        return TurnOrder::FIRST_POKEMON;
    } else if (m1.priority < m2.priority) {
        return TurnOrder::SECOND_POKEMON;
      } else {
          if (p1.calculatedStats.speed > p2.calculatedStats.speed) {
              return TurnOrder::FIRST_POKEMON;
          } else if (p1.calculatedStats.speed < p2.calculatedStats.speed) {
              return TurnOrder::SECOND_POKEMON;
            } else {
              return (rand() % 2 == 0) ? TurnOrder::FIRST_POKEMON : TurnOrder::SECOND_POKEMON;
              }
    }
}

double TextBasedBattle::getCrit() const {
    static std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<int> distribution(1, 16);
    return distribution(generator) == 1 ? 2.0 : 1.0;
}

int TextBasedBattle::GetRandomDamageModifier() const {
    static std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<int> distribution(85, 100);
    return distribution(generator);
}

//get STAB
double GetSTAB(const Pokemon& pokemon, const Move& move) {
    if (std::find(pokemon.types.begin(), pokemon.types.end(), move.type) != pokemon.types.end()) {
        return 1.5;
    }
    return 1.0;
}

double TextBasedBattle::GetSTAB(const Pokemon& pokemon, const Move& move) const {
    return ::GetSTAB(pokemon, move);
}

TurnOrder TextBasedBattle::determineTurnOrder(
    const Pokemon& p1,
    const Pokemon& p2,
    const Move& m1,
    const Move& m2
) const {
    return ::determineTurnOrder(p1, p2, m1, m2);
}


//////////IRONNNNNNNNNNNNNNNNNNNN///////////////////////iron iron iron iron iron iron iron iron iron iron iron iron iron iro nrin riorn irneifen
double TextBasedBattle::TypeEffectivenessCalculator(
    const Move& move,
    const Pokemon& defender
) const {
    // Iron's type effectiveness implementation belongs here.
    (void)move;
    (void)defender;
    return 1.0;
}

//calculate damage
int TextBasedBattle::calculateDamage(
    const Pokemon& attacker,
    const Pokemon& defender,
    const Move& move
) const {
    if (move.power <= 0 || (!isPhysicalMove(move) && !isSpecialMove(move))) {
        return 0;
    }

    const int level = max(1, attacker.level);
    const int attack = isPhysicalMove(move)
        ? max(1, attacker.calculatedStats.attack)
        : max(1, attacker.calculatedStats.spAttack);
    const int defense = isPhysicalMove(move)
        ? max(1, defender.calculatedStats.defense)
        : max(1, defender.calculatedStats.spDefense);

    const double baseDamage =
        ((2.0 * level / 5.0 + 2.0) * move.power * attack / defense) / 50.0 + 2.0;

    //final damage = base x STAB x type x crit (2x or 1x with 1/16 chance) x random (0.85 - 1)

    const double finalDamage =
        baseDamage * GetSTAB(attacker, move)
        * TypeEffectivenessCalculator(move, defender)
        * getCrit()
        * GetRandomDamageModifier() / 100.0;

    return finalDamage > 0.0
        ? max(1, static_cast<int>(finalDamage))
        : 0;
}


//game loop
void TextBasedBattle::startBattle() {


    cout << "Battle started between " << pokemon1.speciesID << " and " << pokemon2.speciesID << "!" << endl;
    // Implement battle logic here

    while (pokemon1.currentHP > 0 && pokemon2.currentHP > 0) {

        //choose move for 1st pokemon
        cout << "Choose a move for " << pokemon1.speciesID << endl;
        for (size_t i = 0; i < pokemon1.learnedMoves.size(); ++i) {
            const Move& move = database.getMove(pokemon1.learnedMoves[i].moveID);
            cout << i + 1 << ". " << move.name << " (PP: " << pokemon1.learnedMoves[i].currentPP << ")" << endl;
        }

        int moveChoice1;
        cin >> moveChoice1;

        if (moveChoice1 < 1 || moveChoice1 > static_cast<int>(pokemon1.learnedMoves.size())) {
            cout << "Invalid move choice. Turn skipped." << endl;
            continue;
        }

        const Move& move1 = database.getMove(pokemon1.learnedMoves[moveChoice1 - 1].moveID);

        //choose move for 2nd pokemon
        cout << "Choose a move for " << pokemon2.speciesID << endl;
        for (size_t i = 0; i < pokemon2.learnedMoves.size(); ++i) {
            const Move& move = database.getMove(pokemon2.learnedMoves[i].moveID);
            cout << i + 1 << ". " << move.name << " (PP: " << pokemon2.learnedMoves[i].currentPP << ")" << endl;
        }

        int moveChoice2;
        cin >> moveChoice2;

        if (moveChoice2 < 1 || moveChoice2 > static_cast<int>(pokemon2.learnedMoves.size())) {
            cout << "Invalid move choice. Turn skipped." << endl;
            continue;
        }

        const Move& move2 = database.getMove(pokemon2.learnedMoves[moveChoice2 - 1].moveID);

        //get turn order
        TurnOrder turnOrder = determineTurnOrder(pokemon1, pokemon2, move1, move2);

        //execute the move

        if (turnOrder == TurnOrder::FIRST_POKEMON) {
            cout << pokemon1.speciesID << " used " << move1.name << "!" << endl;
            // Implement move effect on pokemon2
            
        } else {
            cout << pokemon2.speciesID << " used " << move2.name << "!" << endl;
            // Implement move effect on pokemon1
        }
    }
}