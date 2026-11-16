#pragma once

#include <string>
#include <unordered_map>

#include "moves.h"

std::unordered_map<std::string, Move> loadMoves(const std::string& filePath);