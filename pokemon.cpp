#include <iostream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
using namespace std;


//moves structure

//the moves id enum
enum class MoveID {
    THUNDERBOLT,
    THUNDER_WAVE,
    RECOVER,
    SWORDS_DANCE
};


//the moves category enum
enum class MoveCategory {
    DAMAGE,
    STATUS,
    HEAL,
    STAT_CHANGE
};


//Move srructure
struct Move {
    string name;
    MoveCategory category;
    string type;

    int power;
    int accuracy;
    int pp;
};




//pokemon structure
struct Pokemon {
    string name;
    int level;
    int experience;

    int luck;
    int friendship;

    int hp;

    float iv;
    float ev;

    string type;
    string nature;

    MoveID learnedMoves[4];
};




int main () {


    return 0;
}