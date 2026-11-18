#include "battleMechanics.h"
#include <iostream>
using namespace std;


///////////////////   NOTE   /////////////////////

    //NEED TO ADD:
        //damage calc
        //move categories resolver

        // goodluck _||_ im sleeping 


enum class TurnOrder {
    FIRST_POKEMON,
    SECOND_POKEMON
};

TextBasedBattle::TextBasedBattle() {
    pokemonGenerator generator(database);

    for (const auto& [id, species] : database.getAllPokemons()) {
        PokemonList.push_back(&species);
    }

    pokemon1 = generator.generateRandomPokemon(PokemonList);
    pokemon2 = generator.generateRandomPokemon(PokemonList);
}


//determine turn order
TurnOrder determineTurnOrder(const Pokemon& p1, const Pokemon& p2, Move& m1, Move& m2) {
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


//calculate damage
int TextBasedBattle::calculateDamage(const Pokemon& attacker, const Pokemon& defender, const Move& move) {


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

        Move& move1 = const_cast<Move&>(database.getMove(pokemon1.learnedMoves[moveChoice1 - 1].moveID));

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

        Move& move2 = const_cast<Move&>(database.getMove(pokemon2.learnedMoves[moveChoice2 - 1].moveID));

        //get turn order
        TurnOrder turnOrder = determineTurnOrder(pokemon1, pokemon2, move1, move2);

        //execute the move

        if (turnOrder == TurnOrder::FIRST_POKEMON) {
            cout << pokemon1.speciesID << " used " << move1.name << "!" << endl;
            // Implement move effect on pokemon2
            // For example, reduce HP based on move power and type effectiveness
            
        } else {
            cout << pokemon2.speciesID << " used " << move2.name << "!" << endl;
            // Implement move effect on pokemon1
        }
    }
}