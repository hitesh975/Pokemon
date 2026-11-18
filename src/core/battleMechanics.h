#include "../data/gameDataBase.h"
#include "randomPokemonGenerator.h"
#include <vector>

class TextBasedBattle {
    private:
        GameDataBase database;
        std::vector<const PokemonSpecies*> PokemonList;
        Pokemon pokemon1;
        Pokemon pokemon2;
        
        enum class TurnOrder {
            FIRST_POKEMON,
            SECOND_POKEMON
        };

        TurnOrder determineTurnOrder(const Pokemon& p1, const Pokemon& p2, Move& m1, Move& m2);

        int calculateDamage(const Pokemon& attacker, const Pokemon& defender, const Move& move);
    
    public:
        TextBasedBattle(); // generate 2 pokemons
        void startBattle();
};