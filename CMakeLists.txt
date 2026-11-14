cmake_minimum_required(VERSION 3.20)

project(PokemonBattle)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(nlohmann_json CONFIG REQUIRED)

add_executable(pokemon pokemon.cpp)

target_link_libraries(pokemon PRIVATE nlohmann_json::nlohmann_json)