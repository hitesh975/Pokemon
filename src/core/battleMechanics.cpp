#include "battleMechanics.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <stdexcept>
#include <random>
#include <limits>
#include "moves.h"
using namespace std;

namespace {
bool hasCategory(const Move& move, MoveCategory category) {
    return std::find(move.categories.begin(), move.categories.end(), category) != move.categories.end();
}
}

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

//calculate physical damage
int TextBasedBattle::calculatePhysicalDamage(
    const Pokemon& attacker,
    const Pokemon& defender,
    const Move& move
) const {
    if (!hasCategory(move, MoveCategory::PHYSICAL) || move.power <= 0) {
        return 0;
    }

    const int level = max(1, attacker.level);
    const int attack = max(1, attacker.calculatedStats.attack);
    const int defense = max(1, defender.calculatedStats.defense);

    const double baseDamage =
        ((2.0 * level / 5.0 + 2.0) * move.power * attack / defense) / 50.0 + 2.0;

    const double finalDamage =
        baseDamage * GetSTAB(attacker, move)
        * TypeEffectivenessCalculator(move, defender)
        * getCrit()
        * GetRandomDamageModifier() / 100.0;

    return finalDamage > 0.0
        ? max(1, static_cast<int>(finalDamage))
        : 0;
}

//calculate special damage
int TextBasedBattle::calculateSpecialDamage(
    const Pokemon& attacker,
    const Pokemon& defender,
    const Move& move
) const {
    if (!hasCategory(move, MoveCategory::SPECIAL) || move.power <= 0) {
        return 0;
    }

    const int level = max(1, attacker.level);
    const int attack = max(1, attacker.calculatedStats.spAttack);
    const int defense = max(1, defender.calculatedStats.spDefense);

    const double baseDamage =
        ((2.0 * level / 5.0 + 2.0) * move.power * attack / defense) / 50.0 + 2.0;

    const double finalDamage =
        baseDamage * GetSTAB(attacker, move)
        * TypeEffectivenessCalculator(move, defender)
        * getCrit()
        * GetRandomDamageModifier() / 100.0;

    return finalDamage > 0.0
        ? max(1, static_cast<int>(finalDamage))
        : 0;
}


int TextBasedBattle::MoveResolver(
    Pokemon& attacker,
    Pokemon& defender,
    const Move& move
) const {
    int damage = 0;

    if (hasCategory(move, MoveCategory::PHYSICAL)) {
        damage = calculatePhysicalDamage(attacker, defender, move);
        defender.currentHP = max(0, defender.currentHP - damage);
    }
    if (hasCategory(move, MoveCategory::SPECIAL)) {
        damage = calculateSpecialDamage(attacker, defender, move);
        defender.currentHP = max(0, defender.currentHP - damage);
    }
    if (hasCategory(move, MoveCategory::HEAL)) {
        attacker.currentHP += move.heal;
        attacker.currentHP = min(attacker.calculatedStats.hp, attacker.currentHP);
    }
    if (hasCategory(move, MoveCategory::STATUS)) {
        
    }

    (void)defender;
    return damage;
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
        do {
            moveChoice1 = 0;
            cin >> moveChoice1;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            if (moveChoice1 < 1 || moveChoice1 > static_cast<int>(pokemon1.learnedMoves.size())) {
                cout << "Invalid move choice. Choose a valid move:" << endl;
            }
        } while (moveChoice1 < 1 || moveChoice1 > static_cast<int>(pokemon1.learnedMoves.size()));

        const Move& move1 = database.getMove(pokemon1.learnedMoves[moveChoice1 - 1].moveID);

        //choose move for 2nd pokemon
        cout << "Choose a move for " << pokemon2.speciesID << endl;
        for (size_t i = 0; i < pokemon2.learnedMoves.size(); ++i) {
            const Move& move = database.getMove(pokemon2.learnedMoves[i].moveID);
            cout << i + 1 << ". " << move.name << " (PP: " << pokemon2.learnedMoves[i].currentPP << ")" << endl;
        }

        int moveChoice2;
        do {
            moveChoice2 = 0;
            cin >> moveChoice2;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            if (moveChoice2 < 1 || moveChoice2 > static_cast<int>(pokemon2.learnedMoves.size())) {
                cout << "Invalid move choice. Choose a valid move:" << endl;
            }
        } while (moveChoice2 < 1 || moveChoice2 > static_cast<int>(pokemon2.learnedMoves.size()));

        const Move& move2 = database.getMove(pokemon2.learnedMoves[moveChoice2 - 1].moveID);

        //get turn order
        TurnOrder turnOrder = determineTurnOrder(pokemon1, pokemon2, move1, move2);

        //execute the move

        if (turnOrder == TurnOrder::FIRST_POKEMON) {
            cout << pokemon1.speciesID << " used " << move1.name << "!" << endl;
            const int damage = MoveResolver(pokemon1, pokemon2, move1);

            cout << damage << " damage dealt!" << endl;
        } else {
            cout << pokemon2.speciesID << " used " << move2.name << "!" << endl;
            const int damage = MoveResolver(pokemon2, pokemon1, move2);

            cout << damage << " damage dealt!" << endl;
        }
    }
}
