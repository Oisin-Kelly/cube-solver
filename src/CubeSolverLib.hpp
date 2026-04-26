#pragma once
#include "Face.hpp"
#include <array>
#include <string>
#include <vector>

struct SolveResult
{
    bool success;
    std::vector<std::string> moves;
    std::string error;
};

SolveResult solveCube(const std::array<Face, 54> &state, size_t maxMoves = 1000);
std::string moveToNotation(Face face, int turns);
std::vector<std::tuple<Face, int>> optimiseMoves(std::vector<std::tuple<Face, int>> moves);
