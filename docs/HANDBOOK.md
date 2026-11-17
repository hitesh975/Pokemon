# Pokemon Battle RPG: Project Handbook

This handbook describes the repository as it currently exists. The project is an early C++20 learning and game-development project: it has JSON data loaders, basic game data types, and a stat calculator, but it does not yet provide a playable battle game. In particular, some source files are prototypes that are not included in the CMake build.

The README describes the project's goals and setup. Where its feature summary may sound more complete than the code, this handbook distinguishes implemented code from unfinished or unwired code.

## 1. Project overview and objectives

The stated goal is to build an original, turn-based creature-battling RPG inspired by classic Pokemon battle mechanics. The README describes learning C++, modular software architecture, data management, and implementing game mechanics as project objectives.

The current implementation provides:

- Species and move definitions in JSON.
- C++ types for stats, natures, moves, species, and individual Pokemon.
- Functions for parsing the JSON datasets into C++ records.
- A `GameDataBase` class that owns loaded species and move maps.
- A stat calculator for six stats and five natures.
- Small standalone programs for demonstrating or checking pieces of the code.

The current `pokemon` executable is only a stub: `main()` immediately returns. There is no playable interface, turn loop, battle resolution, save system, or complete Pokemon-generation workflow.

## 2. Repository structure

This is the tracked project structure. Generated build output and the locally installed vcpkg checkout are intentionally omitted.

```text
.
|-- .gitignore
|-- CMakeLists.txt
|-- README.md
|-- vcpkg.JSON
|-- dataset/
|   |-- moves.JSON
|   `-- pokemons.JSON
|-- docs/
|   `-- HANDBOOK.md
`-- src/
    |-- app/
    |   `-- pokemon.cpp
    |-- core/
    |   |-- calculateStats.cpp
    |   |-- moves.h
    |   |-- pokemons.h
    |   |-- randomPokemonGenerator.cpp
    |   |-- randomPokemonGenerator.h
    |   `-- stats.h
    |-- data/
    |   |-- gameDataBase.cpp
    |   |-- gameDataBase.h
    |   |-- loadmoves.cpp
    |   |-- loadmoves.h
    |   |-- loadpokemons.cpp
    |   `-- loadpokemons.h
    `-- tests/
        |-- test_GameDataBase.cpp
        |-- test_pokemons.cpp
        `-- test_stats.cpp
```

### Top-level files

- `CMakeLists.txt` sets C++20, finds `nlohmann_json`, and defines the three targets currently configured in CMake.
- `vcpkg.JSON` declares `nlohmann-json` as the vcpkg dependency.
- `README.md` gives a short project overview and a MinGW/vcpkg-oriented setup and test recipe.
- `.gitignore` excludes `/vcpkg/`, `/build/`, common CMake build directories, compiled binaries and objects, editor files, temporary files, logs, and common Windows metadata files.
- `dataset/` contains the JSON input files. The loaders expect paths relative to the process's current working directory.
- `docs/HANDBOOK.md` is this guide.
- `src/app/` contains the application entry point.
- `src/core/` contains game data types and calculations, along with an unfinished generator.
- `src/data/` contains JSON loaders and the database wrapper.
- `src/tests/` contains three standalone test/demo source files. Only two are CMake targets.

## 3. Types, classes, and enums

### `Stats` (`src/core/stats.h`)

A plain struct with six integer fields, in this order: `hp`, `attack`, `defense`, `spAttack`, `spDefense`, and `speed`. The same structure is used for species base stats, individual values (IVs), effort values (EVs), and calculated stats. The struct itself does not enforce ranges or distinguish which role a value represents.

### `Nature` (`src/core/stats.h`)

An enum class containing the five natures currently used by the calculator:

- `HARDY`: neutral.
- `ADAMANT`: Attack increased, Special Attack decreased.
- `MODEST`: Special Attack increased, Attack decreased.
- `JOLLY`: Speed increased, Special Attack decreased.
- `BOLD`: Defense increased, Attack decreased.

These are the only nature values in the current enum and in the generator's random range.

### `StatType` (`src/core/stats.h`)

An enum class naming the six stats: `HP`, `ATTACK`, `DEFENSE`, `SP_ATTACK`, `SP_DEFENSE`, and `SPEED`. `getNatureMultiplier` uses it to choose which non-neutral nature modifier applies.

### `MoveCategory` (`src/core/moves.h`)

An enum class with `DAMAGE`, `STATUS`, `HEAL`, and `STAT_CHANGE`. The JSON conversion function also accepts `PHYSICAL` and `SPECIAL`, but currently maps both to `DAMAGE`; physical and special damage are not represented as distinct enum values.

### `PokemonType` (`src/core/moves.h`)

An enum class for the 18 types supported by the current conversion function: `FIRE`, `WATER`, `GRASS`, `ELECTRIC`, `NORMAL`, `FLYING`, `PSYCHIC`, `GROUND`, `ROCK`, `ICE`, `BUG`, `POISON`, `FIGHTING`, `GHOST`, `DRAGON`, `DARK`, `STEEL`, and `FAIRY`.

### `LearnableMove` (`src/core/moves.h`)

A small record with a move ID string and the integer level at which a species can learn it. It stores a reference by ID rather than embedding a full `Move`.

### `Move` (`src/core/moves.h`)

A move record containing:

- `id` and `name`.
- `category` and `type`.
- Integer `power`, `accuracy`, and `pp`.
- An `effect` string and integer `effectChance`.

Effect text is stored as data only. No current system interprets or applies those effects in battle.

### `PokemonSpecies` (`src/core/pokemons.h`)

A species record containing its string `id`, display `name`, vector of `PokemonType` values, `baseStats`, and vector of `LearnableMove` entries. It represents species-level data, not an individual creature with a level or IVs.

### `Pokemon` (`src/core/randomPokemonGenerator.h`)

The proposed individual-creature record. It contains a species ID, level, experience, friendship, nature, IVs, EVs, and an array of four learned move IDs. There are no constructors or validation rules in the struct, and the current generator does not successfully populate and return one.

### `pokemonGenerator` (`src/core/randomPokemonGenerator.h`)

A class intended to generate individual Pokemon. It holds a `const GameDataBase&` and an `std::mt19937` random engine. Its implementation is incomplete and is not included in any configured CMake target. `generateRandomPokemon` accepts a vector of species, separately from the database reference.

### `GameDataBase` (`src/data/gameDataBase.h`)

A class that owns two unordered maps: moves keyed by move ID and species keyed by species ID. Its constructor loads both datasets. It provides lookup methods that return references to stored records. It is implemented and has a test source, but CMake currently does not build it into any target.

### `BattleState` (`src/app/pokemon.cpp`)

A struct local to the application source, with `currentHP` and stage fields for Attack, Defense, Special Attack, Special Defense, and Speed. The stage fields default to zero; `currentHP` has no default initializer. Nothing currently constructs or uses this struct.

## 4. Functions and responsibilities

This section includes the functions declared or defined in the current source, including inline conversions and test `main()` functions.

### Type conversions (`src/core/moves.h`)

- `stringToMoveCategory(categoryStr)` converts supported uppercase category strings to `MoveCategory`. `"DAMAGE"`, `"PHYSICAL"`, and `"SPECIAL"` all return `DAMAGE`; `"STATUS"`, `"HEAL"`, and `"STAT_CHANGE"` map to their corresponding values. Any other string throws `std::invalid_argument`.
- `stringToPokemonType(typeStr)` converts one of the 18 supported uppercase type strings to `PokemonType`. An unrecognized string throws `std::invalid_argument`.

### Stat functions (`src/core/stats.h`, `src/core/calculateStats.cpp`)

- `getNatureMultiplier(nature, stat)` returns `1.1` for the boosted stat, `0.9` for the lowered stat, or `1.0` otherwise. It is neutral for HP for every current nature.
- `calculate_HP(baseHP, HPIV, HPEV, level)` computes HP using the HP formula described below.
- `calculate_NON_HP(baseStat, IV, EV, level, natureMultiplier)` computes one non-HP stat, applies the supplied multiplier, and converts the result to `int`.
- `calculateStats(baseStats, ivs, evs, level, nature)` calculates all six stats, requesting the appropriate multiplier for each non-HP stat, and returns a new `Stats` record.

These functions do not validate level, IV, EV, or stat ranges.

### Species loading (`src/data/loadpokemons.h`, `src/data/loadpokemons.cpp`)

- `loadPokemonSpeciesFromJson()` searches for `dataset/pokemons.JSON`, then `dataset/pokemons.json`. It parses the root `species` array, converts each entry into a `PokemonSpecies`, and returns an `unordered_map` keyed by ID. It explicitly checks that `species` exists and is an array, and rejects duplicate species IDs with `std::runtime_error`. JSON parse errors, absent required fields, type conversion errors, invalid type names, and file errors can also surface as exceptions.

### Move loading (`src/data/loadmoves.h`, `src/data/loadmoves.cpp`)

- `loadMoves(filePath)` tries the caller-supplied path first, followed by `dataset/moves.JSON` and `dataset/moves.json` (empty paths are skipped). It parses the root `moves` array and converts each entry into a `Move`, returning a map keyed by move ID. File-open failure throws `std::runtime_error`; JSON and conversion exceptions can also propagate. It does not explicitly check the root key or reject duplicate IDs; assigning a repeated ID replaces the previous map value.

### Database (`src/data/gameDataBase.h`, `src/data/gameDataBase.cpp`)

- `GameDataBase::GameDataBase()` loads moves by calling `loadMoves("dataset/moves.json")`, then loads species by calling `loadPokemonSpeciesFromJson()`. The move loader falls back to the uppercase dataset filename used in this repository. Paths are relative to the current working directory.
- `GameDataBase::getMove(id)` finds a move by ID and returns a const reference; if it is absent, it throws `std::runtime_error`.
- `GameDataBase::getPokemon(id)` finds a species by ID and returns a const reference; if it is absent, it throws `std::runtime_error`.

### Generator (`src/core/randomPokemonGenerator.h`, `src/core/randomPokemonGenerator.cpp`)

- `pokemonGenerator::pokemonGenerator(database)` stores a reference to the supplied database and seeds its `std::mt19937` using `std::random_device`.
- `pokemonGenerator::generateRandomPokemon(pokemonList)` selects a species using `randomEngine() % pokemonList.size()`, generates IVs, a nature, a level, and a list of learnable moves. **It currently does not create or return the declared `Pokemon` result.** It also has no empty-list check, so an empty vector leads to invalid modulo/indexing behavior.
- `pokemonGenerator::generateIVs()` independently samples each of the six IV values uniformly from 0 through 31 and returns them in `Stats` field order.
- `pokemonGenerator::generateNature()` samples an integer from 0 through 4 and converts it to the current `Nature` enum values.
- `pokemonGenerator::generateLevel()` samples an integer from 0 through 100 inclusive. This permits level 0; no further validation is performed.
- `pokemonGenerator::generateLearnedMoves(species, level)` walks the species' learnable-move entries in their stored order, appending eligible move IDs (`move.level <= level`) until it has four. Despite a nearby comment about finding the highest-level move, the actual code does not sort or select the highest four; its result depends on JSON order.
- `pokemonGenerator::getBaseStats(speciesID)` calls `database.getPokemon(speciesID)` and returns a const reference to that species' base stats. This is the generator's direct database lookup path; the current `generateRandomPokemon` body does not call it.
- `pokemonGenerator::calculateStats(baseStats, ivs, evs, level, nature)` currently calls `calculateStats` with the same arguments from inside a member function of that name. The unqualified call resolves back to the member function, so if used it recurses rather than calling the global calculator. The generator is currently excluded from the build, and this member has no current caller.

### Application and test entry points

- `main()` in `src/app/pokemon.cpp` immediately returns zero. The local `BattleState` type is not used.
- `main()` in `src/tests/test_stats.cpp` creates sample base stats, IVs, EVs, level, and nature; invokes the global stat calculator; and prints each resulting stat. It is a demonstration, not an assertion-based test.
- `main()` in `src/tests/test_pokemons.cpp` loads the species dataset and uses `assert` to check the species count, Cindercub's name, type count, selected base stats, and first learnable move.
- `main()` in `src/tests/test_GameDataBase.cpp` constructs the database, checks lookups for Cindercub and Ember, and checks that an invalid move ID throws. This test source is not currently a CMake target.

## 5. JSON datasets

Both datasets are ordinary JSON text with uppercase `.JSON` filenames in the repository. String enum values are uppercase, and IDs are strings.

### Species dataset: `dataset/pokemons.JSON`

The root object has a `species` array. There are currently nine species, with IDs `"001"` through `"009"`. Each array item has this shape:

```json
{
  "id": "001",
  "name": "Cindercub",
  "types": ["FIRE"],
  "baseStats": {
    "hp": 45,
    "attack": 55,
    "defense": 40,
    "spAttack": 65,
    "spDefense": 45,
    "speed": 65
  },
  "learnableMoves": [
    { "level": 1, "moveID": "tackle" },
    { "level": 5, "moveID": "ember" }
  ]
}
```

The loader expects every listed property and converts its values to the corresponding C++ type. The current sample's `learnableMoves` are listed in an order that the generator later preserves; no sorting is performed by the loader.

### Move dataset: `dataset/moves.JSON`

The root object has a `moves` array. There are currently 15 move records. A move has this shape:

```json
{
  "id": "ember",
  "name": "Ember",
  "category": "SPECIAL",
  "type": "FIRE",
  "power": 40,
  "accuracy": 100,
  "pp": 25,
  "effect": "BURN",
  "effectChance": 10
}
```

`effect` is an uninterpreted string, including the empty string for moves without a listed effect. The JSON category `"PHYSICAL"` or `"SPECIAL"` is collapsed to `MoveCategory::DAMAGE`, so the loader does not retain the distinction. The current loader does not validate that every species `moveID` refers to an existing move.

When adding or changing dataset content, keep IDs consistent across both files and use only values recognized by the string conversion functions. The current loader expects all the documented fields and does not provide defaults for omitted values.

## 6. How data loading works

The high-level path is:

```text
dataset/*.JSON
    -> nlohmann::json parses the file
    -> loader reads fields and converts strings/enums
    -> C++ structs stored in unordered_maps/vectors
    -> callers use the returned records or GameDataBase lookups
```

`loadPokemonSpeciesFromJson()` always uses its built-in candidate paths and returns a fresh species map. `loadMoves()` accepts a preferred path but has built-in fallback paths. Both paths are relative to the program's working directory, not to the source file or executable. Run test executables from the repository root.

The species loader has a top-level shape check and explicit duplicate-ID detection. The move loader directly indexes `moveData["moves"]` and assigns with `moves[move.id]`; malformed or duplicate move data is not handled identically to species data. In both loaders, JSON parsing and typed field extraction can throw. The loaders do not catch these exceptions.

## 7. GameDataBase and its relationship to other systems

`GameDataBase` is the repository's combined lookup abstraction:

1. Constructing it calls the move loader and the species loader.
2. The resulting maps are retained as private members for the object's lifetime.
3. Callers request a record by its string ID.
4. The lookup returns a const reference; a missing ID throws rather than returning an empty value.

The generator takes a `const GameDataBase&` and `getBaseStats()` uses `getPokemon()` to retrieve species data. However, the generator's current generation method does not yet use this lookup, and neither the app nor the configured test targets use `GameDataBase`. The database test source demonstrates intended lookup behavior, but CMake does not currently build it.

The database has no database file, SQL engine, persistence, or mutation API; it is an in-memory wrapper around the JSON-loaded maps.

## 8. Stat calculation

The global `calculateStats()` in `src/core/calculateStats.cpp` uses the project's `Stats` structure for each input:

- `baseStats`: species' base values.
- `ivs`: individual values.
- `evs`: effort values.
- `level`: integer level.
- `nature`: modifier selection.

The implemented equations are:

```text
HP = ((2 * baseHP + HPIV + (HPEV / 4)) * level) / 100
     + level + 10

Other stat = (((2 * baseStat + IV + (EV / 4)) * level) / 100
              + 5) * nature multiplier
```

In C++, `EV / 4` is integer division (equivalent to floor for the nonnegative values normally expected); the HP calculation also uses integer arithmetic throughout. For non-HP stats, division by `100.0` is floating point; multiplying by the nature modifier produces a double, which is truncated toward zero when cast to `int`. HP never receives a nature modifier. For the neutral stat in a nature, `getNatureMultiplier()` returns `1.0`.

The calculator only computes stats: it does not read a species from JSON or `GameDataBase`, does not store results in a `Pokemon`, and does not enforce game rules or input ranges. `test_stats` illustrates one sample invocation and prints the output.

## 9. Current Pokemon generation implementation

The generator is a prototype, not an operational feature:

- It has helper functions for random IVs, nature, level, and eligible learnable move IDs.
- Species selection is from the vector passed to `generateRandomPokemon`, using the generator's random engine.
- It stores a database reference and has a helper for looking up species base stats.
- There is no implementation that assembles the selected values into a `Pokemon` and returns it.
- EVs, experience, friendship, calculated stats, and the four-element `Pokemon::learnedMoves` array are not populated by the generation method.
- It is not listed in any CMake target.
- `randomPokemonGenerator.h` includes `./data/gameDataBase.h`; relative to that header, this points under `src/core/data/`, while the database header is under `src/data/`. Because the generator is not compiled by the current build, this include path has not been validated by a configured target.
- The member `calculateStats` helper currently recurses into itself if called.
- The species selection assumes a nonempty vector; the level distribution includes zero.
- The move-selection helper returns the first up to four eligible entries in source order, not necessarily the highest-level four.

Because it is excluded from the build, its compile/runtime behavior is not covered by the repository's configured build or tests. Do not rely on it as a working API without completing and testing it.

## 10. How the systems interact today

At source level, the intended connections are:

```text
JSON files --loaders--> species/move records --GameDataBase--> ID lookups
                                                    ^
                                                    |
                                      pokemonGenerator (prototype)

base stats + IVs + EVs + level + nature --> calculateStats() --> Stats result
```

In the configured executable, these connections are not assembled into a game flow. `pokemon` compiles the app source, stat calculator, and JSON loader sources, but its `main()` calls none of them. `GameDataBase` and `pokemonGenerator` are not included in the CMake targets. The stat calculator is exercised by the `test_stats` demonstration; the species loader is exercised by `test_pokemons`.

## 11. Compile and run

### Requirements

- CMake 3.20 or newer.
- A compiler with C++20 support.
- vcpkg to provide `nlohmann-json`.
- For the README's example configuration: MinGW and the `x64-mingw-dynamic` vcpkg triplet.

The README's setup expects a vcpkg checkout nested in the repository root. From the project root in PowerShell, one way to follow that setup is:

```powershell
git clone https://github.com/microsoft/vcpkg.git vcpkg
.\vcpkg\bootstrap-vcpkg.bat

cmake -S . -B build -G "MinGW Makefiles" `
  -DCMAKE_TOOLCHAIN_FILE="$PWD/vcpkg/scripts/buildsystems/vcpkg.cmake" `
  -DVCPKG_TARGET_TRIPLET=x64-mingw-dynamic `
  -DVCPKG_HOST_TRIPLET=x64-mingw-dynamic

cmake --build build
```

This assumes the matching MinGW compiler and make program are installed and discoverable. Choose a CMake generator and vcpkg triplet compatible with your compiler if using another toolchain. The vcpkg manifest installs the `nlohmann-json` package required by `find_package(nlohmann_json CONFIG REQUIRED)`.

Run the application from the repository root:

```powershell
.\build\pokemon.exe
```

It currently exits immediately without starting a game. On other platforms, the executable filename may not have an `.exe` extension.

### Configured CMake targets

- `pokemon` compiles `src/app/pokemon.cpp`, `src/core/calculateStats.cpp`, `src/data/loadpokemons.cpp`, and `src/data/loadmoves.cpp`; it links `nlohmann_json`.
- `test_stats` compiles `src/tests/test_stats.cpp` and `src/core/calculateStats.cpp`.
- `test_pokemons` compiles `src/tests/test_pokemons.cpp` and both JSON loader implementation files; it links `nlohmann_json`.

`src/data/gameDataBase.cpp`, `src/tests/test_GameDataBase.cpp`, and both random-generator files are not included in the current CMake targets.

## 12. Run the existing tests

Build first, then run from the repository root so the relative dataset paths work:

```powershell
.\build\test_stats.exe
.\build\test_pokemons.exe
```

The first program prints six calculated stats for a hard-coded sample. It has no assertions, so successful execution only demonstrates that the sample call completes.

The second program uses `assert` to check that the species loader returns nine entries, that species `"001"` is named Cindercub, and that selected type/stat/move data matches expectations.

`test_GameDataBase.cpp` contains assertions for database lookups and missing-move errors, but it is not wired to a CMake target. CMake does not call `enable_testing()` or `add_test()`, so there are currently no registered CTest tests. Assertions may also be disabled by build configurations that define `NDEBUG`.

## 13. Coding conventions and contribution guidance

### Observed conventions

There is no tracked `CONTRIBUTING.md`, formatter configuration, linter configuration, or formal style guide. The conventions visible in the existing code are:

- C++20, with `.h` headers and `.cpp` implementation files.
- `#pragma once` in headers.
- Types use PascalCase (`PokemonSpecies`, `GameDataBase`); functions and methods generally use camelCase, with older stat function names such as `calculate_HP` and `calculate_NON_HP`.
- Dataset keys use camelCase where composed (`baseStats`, `learnableMoves`, `moveID`, `effectChance`), while enum values and type/category strings are uppercase.
- Many records are simple structs; lookup maps use `std::unordered_map` and ordered lists use `std::vector`.
- Errors in loading and missing database lookups are surfaced using standard exceptions.
- The tests are independent executable programs and use `assert` for checks.

These are observations, not enforced project-wide rules. Existing style is inconsistent in places, including spacing, include ordering, and use of `using namespace std`.

### Practical contributor workflow

These are safe recommendations for contributors, not formal repository policy:

1. Check the CMake target list before assuming a source file is compiled. Add new implementations and tests to CMake as needed.
2. Keep JSON IDs and enum string values aligned with the C++ lookup/conversion code.
3. Run the relevant configured executable after a change, from the repository root.
4. When adding a behavior, add a focused test that exercises it; remember that the database test currently needs CMake wiring before it can run as part of the build.
5. Treat files under `build/` and the local `vcpkg/` checkout as generated/dependency content, not source.
6. Update this handbook when the actual build targets or behavior change.

## 14. Completed, incomplete, and planned functionality

### Present in source and currently built or directly exercised

- C++20 CMake project and vcpkg declaration for `nlohmann-json`.
- JSON loading of species and moves.
- In-memory species and move record types.
- Six-stat calculation with five natures.
- Standalone stat demonstration and species-loader assertion program.
- Minimal `pokemon` executable target.

### Implemented in source but not wired into the current CMake build

- `GameDataBase`, its lookup methods, and `test_GameDataBase.cpp`.
- `pokemonGenerator` and its helper functions.

The generator is incomplete and contains the limitations described above; its presence in source does not mean generation is usable.

### Not implemented as working gameplay

- A playable application flow, menus, or user input.
- Battle turn processing, move execution, damage/effect resolution, or win/loss handling.
- Applying move effects from the `effect` strings.
- A complete random Pokemon constructor/return path.
- Persistence, saves, parties, or progression.
- A configured test runner/CTest suite.

The README states the broader RPG as the project goal. The repository does not document detailed specifications or delivery plans for these future systems, so their exact design and schedule are uncertain.
