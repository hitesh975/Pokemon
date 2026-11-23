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

static std::mt19937 generator(std::random_device{}());

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
    std::uniform_int_distribution<int> distribution(1, 16);
    return distribution(generator) == 1 ? 2.0 : 1.0;
}





int TextBasedBattle::GetRandomDamageModifier() const {
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





//status effects
    void TextBasedBattle::HandleStatusEffects(
    const Move& move,
    Pokemon& pokemon,
    bool which //which pokemon
    ) {
        (void)which;

    //none
    if (move.effect == MoveEffect::NONE) {
        pokemon.Status = MoveEffect::NONE;


    } else if (move.effect == MoveEffect::BURN) {         //BURN
        pokemon.Status = MoveEffect::BURN;
        //halve the pokemons atack outside of this function probably in damage calculator formula
        pokemon.currentHP -= pokemon.calculatedStats.hp / 16;
        StatusMessage = pokemon.speciesID + " is hurt by its burn";


    } else if (move.effect == MoveEffect::FREEZE) {       //FREEZE
        pokemon.Status = MoveEffect::FREEZE;
        StatusMessage = pokemon.speciesID + " is frozen solid";


    } else if (move.effect == MoveEffect::PARALYZE) {     //PARALYZE
        pokemon.Status = MoveEffect::PARALYZE;
        StatusMessage = pokemon.speciesID + " is paralysed";


    } else if (move.effect == MoveEffect::POISON) {       //POSION
        StatusMessage = pokemon.speciesID + " is poisoned";
        pokemon.Status = MoveEffect::POISON;
        pokemon.currentHP -= pokemon.calculatedStats.hp / 16;

    } else if (move.effect == MoveEffect::SLEEP) {        //SLEP
        pokemon.Status = MoveEffect::SLEEP;
        StatusMessage = pokemon.speciesID + " is fast asleep";
    }

}





//game loop
void TextBasedBattle::startBattle() {
    cout << "Battle started between " << pokemon1.speciesID << " and " << pokemon2.speciesID << "!" << endl;
    bool noMovesRemaining = false;

    while (pokemon1.currentHP > 0 && pokemon2.currentHP > 0) {
        Pokemon1CanAttack = true;
        Pokemon2CanAttack = true;

        const auto chooseMove = [this](Pokemon& pokemon) {
            bool hasPP = false;
            for (const PokemonMove& learnedMove : pokemon.learnedMoves) {
                if (learnedMove.currentPP > 0) {
                    hasPP = true;
                    break;
                }
            }

            if (!hasPP) {
                cout << pokemon.speciesID << " has no moves with PP remaining." << endl;
                return -1;
            }

            cout << "Choose a move for " << pokemon.speciesID << endl;
            for (size_t i = 0; i < pokemon.learnedMoves.size(); ++i) {
                const PokemonMove& learnedMove = pokemon.learnedMoves[i];
                const Move& move = database.getMove(learnedMove.moveID);
                cout << i + 1 << ". " << move.name << " (PP: "
                     << learnedMove.currentPP << "/" << move.pp << ")" << endl;
            }

            int moveChoice = 0;
            while (true) {
                cin >> moveChoice;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                } else if (
                    moveChoice >= 1
                    && moveChoice <= static_cast<int>(pokemon.learnedMoves.size())
                    && pokemon.learnedMoves[moveChoice - 1].currentPP > 0
                ) {
                    return moveChoice - 1;
                }

                cout << "Invalid move choice or no PP remaining. Choose a valid move:" << endl;
            }
        };

        const int moveIndex1 = chooseMove(pokemon1);
        const int moveIndex2 = chooseMove(pokemon2);
        if (moveIndex1 < 0 && moveIndex2 < 0) {
            noMovesRemaining = true;
            break;
        }

        const Move* move1 = moveIndex1 >= 0
            ? &database.getMove(pokemon1.learnedMoves[moveIndex1].moveID)
            : nullptr;
        const Move* move2 = moveIndex2 >= 0
            ? &database.getMove(pokemon2.learnedMoves[moveIndex2].moveID)
            : nullptr;

        const auto executeMove = [this](
            Pokemon& attacker,
            Pokemon& defender,
            PokemonMove& learnedMove,
            const Move& move,
            bool attackerIsPokemon1
        ) {
            bool& canAttack = attackerIsPokemon1 ? Pokemon1CanAttack : Pokemon2CanAttack;
            if (!canAttack) {
                return;
            }

            if (attacker.Status == MoveEffect::FREEZE) {
                canAttack = false;
                cout << attacker.speciesID << " is frozen solid and cannot move!" << endl;
            } else if (attacker.Status == MoveEffect::SLEEP) {
                canAttack = false;
                cout << attacker.speciesID << " is fast asleep and cannot move!" << endl;
            } else if (attacker.Status == MoveEffect::PARALYZE) {
                std::uniform_int_distribution<int> distribution(1, 4);
                if (distribution(generator) == 1) {
                    canAttack = false;
                    cout << attacker.speciesID << " is paralysed and cannot move!" << endl;
                }
            }
            if (!canAttack) {
                return;
            }

            --learnedMove.currentPP;

            bool hit = move.accuracy >= 100;
            if (!hit && move.accuracy > 0) {
                std::uniform_int_distribution<int> distribution(1, 100);
                hit = distribution(generator) <= move.accuracy;
            }
            if (!hit) {
                cout << attacker.speciesID << "'s " << move.name << " missed!" << endl;
                return;
            }

            cout << attacker.speciesID << " used " << move.name << "!" << endl;
            const int damage = MoveResolver(attacker, defender, move);
            cout << damage << " damage dealt!" << endl;

            if (defender.currentHP > 0 && move.effect != MoveEffect::NONE) {
                bool effectApplied = move.effectChance >= 100;
                if (!effectApplied && move.effectChance > 0) {
                    std::uniform_int_distribution<int> distribution(1, 100);
                    effectApplied = distribution(generator) <= move.effectChance;
                }
                if (effectApplied) {
                    HandleStatusEffects(move, defender, !attackerIsPokemon1);
                    cout << StatusMessage << endl;
                    StatusMessage.clear();
                }
            }
        };

        if (move1 != nullptr && move2 != nullptr) {
            const TurnOrder turnOrder = determineTurnOrder(pokemon1, pokemon2, *move1, *move2);
            if (turnOrder == TurnOrder::FIRST_POKEMON) {
                executeMove(pokemon1, pokemon2, pokemon1.learnedMoves[moveIndex1], *move1, true);
                if (pokemon2.currentHP <= 0) {
                    cout << pokemon2.speciesID << " fainted!" << endl;
                    break;
                }
                executeMove(pokemon2, pokemon1, pokemon2.learnedMoves[moveIndex2], *move2, false);
                if (pokemon1.currentHP <= 0) {
                    cout << pokemon1.speciesID << " fainted!" << endl;
                    break;
                }
            } else {
                executeMove(pokemon2, pokemon1, pokemon2.learnedMoves[moveIndex2], *move2, false);
                if (pokemon1.currentHP <= 0) {
                    cout << pokemon1.speciesID << " fainted!" << endl;
                    break;
                }
                executeMove(pokemon1, pokemon2, pokemon1.learnedMoves[moveIndex1], *move1, true);
                if (pokemon2.currentHP <= 0) {
                    cout << pokemon2.speciesID << " fainted!" << endl;
                    break;
                }
            }
        } else if (move1 != nullptr) {
            executeMove(pokemon1, pokemon2, pokemon1.learnedMoves[moveIndex1], *move1, true);
            if (pokemon2.currentHP <= 0) {
                cout << pokemon2.speciesID << " fainted!" << endl;
                break;
            }
        } else {
            executeMove(pokemon2, pokemon1, pokemon2.learnedMoves[moveIndex2], *move2, false);
            if (pokemon1.currentHP <= 0) {
                cout << pokemon1.speciesID << " fainted!" << endl;
                break;
            }
        }
    }

    if (noMovesRemaining) {
        cout << "The battle ended because neither Pokemon has PP remaining." << endl;
    }

    if (pokemon1.currentHP <= 0 && pokemon2.currentHP <= 0) {
        cout << "The battle ended in a draw!" << endl;
    } else if (pokemon1.currentHP <= 0) {
        cout << pokemon2.speciesID << " wins the battle!" << endl;
        cout << "Battle ended!" << endl;
    } else if (pokemon2.currentHP <= 0) {
        cout << pokemon1.speciesID << " wins the battle!" << endl;
        cout << "Battle ended!" << endl;
    }
}
