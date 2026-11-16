cmake_minimum_required(VERSION 3.20)

project(PokemonBattle)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(nlohmann_json CONFIG REQUIRED)

add_executable(pokemon
    src/pokemon.cpp
    src/calculateStats.cpp
    src/loadpokemons.cpp
    src/loadmoves.cpp
)

target_include_directories(pokemon PRIVATE src)
target_link_libraries(pokemon PRIVATE nlohmann_json::nlohmann_json)

add_executable(test_stats
    src/test_stats.cpp
    src/calculateStats.cpp
)

target_include_directories(test_stats PRIVATE src)

add_executable(test_pokemons
    src/test_pokemons.cpp
    src/loadpokemons.cpp
    src/loadmoves.cpp
)

target_include_directories(test_pokemons PRIVATE src)
target_link_libraries(test_pokemons PRIVATE nlohmann_json::nlohmann_json)