cmake_minimum_required(VERSION 3.20)

project(PokemonBattle)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(nlohmann_json CONFIG REQUIRED)

add_executable(pokemon
    src/app/pokemon.cpp
    src/core/calculateStats.cpp
    src/data/loadpokemons.cpp
    src/data/loadmoves.cpp
)

target_include_directories(pokemon PRIVATE src/core src/data)
target_link_libraries(pokemon PRIVATE nlohmann_json::nlohmann_json)

add_executable(test_stats
    src/tests/test_stats.cpp
    src/core/calculateStats.cpp
)

target_include_directories(test_stats PRIVATE src/core)

add_executable(test_pokemons
    src/tests/test_pokemons.cpp
    src/data/loadpokemons.cpp
    src/data/loadmoves.cpp
)

target_include_directories(test_pokemons PRIVATE src/core src/data)
target_link_libraries(test_pokemons PRIVATE nlohmann_json::nlohmann_json)

add_executable(test_random_pokemon
    src/tests/test_randomPokemonGenerator.cpp
    src/core/randomPokemonGenerator.cpp
    src/core/calculateStats.cpp
    src/data/gameDataBase.cpp
    src/data/loadpokemons.cpp
    src/data/loadmoves.cpp
)

target_include_directories(test_random_pokemon PRIVATE src/core src/data)
target_link_libraries(test_random_pokemon PRIVATE nlohmann_json::nlohmann_json)