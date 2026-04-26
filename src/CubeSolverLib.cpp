#include "CubeSolverLib.hpp"
#include "Cube.hpp"
#include "Constants.hpp"
#include "CrossSolver.hpp"
#include "CornerSolver.hpp"
#include "EdgesSolver.hpp"
#include "BottomSolver.hpp"
#include <stdexcept>

std::vector<std::tuple<Face, int>> optimiseMoves(std::vector<std::tuple<Face, int>> moves)
{
    bool changed = true;
    while (changed)
    {
        changed = false;
        for (int i = 0; i + 1 < (int)moves.size();)
        {
            if (std::get<0>(moves[i]) == std::get<0>(moves[i + 1]))
            {
                int merged = (std::get<1>(moves[i]) + std::get<1>(moves[i + 1])) % 4;
                moves.erase(moves.begin() + i + 1);
                if (merged == 0)
                    moves.erase(moves.begin() + i);
                else
                    std::get<1>(moves[i]) = merged;
                changed = true;
            }
            else
                ++i;
        }
    }
    return moves;
}

std::string moveToNotation(Face face, int turns)
{
    const char faceLetters[] = {'U', 'F', 'R', 'B', 'L', 'D'};
    char letter = faceLetters[static_cast<int>(face)];

    int normalized = ((turns % 4) + 4) % 4;
    if (normalized == 1)
        return std::string(1, letter);
    if (normalized == 3)
        return std::string(1, letter) + "'";
    return std::string(1, letter) + "2";
}

SolveResult solveCube(const std::array<Face, 54> &state, size_t maxMoves)
{
    Cube cube(state);
    cube.setMaxMoves(maxMoves);

    try
    {
        CrossSolver(&cube).solve();
        CornerSolver(&cube).solve();
        EdgesSolver(&cube).solve();
        BottomSolver(&cube).solve();
    }
    catch (const std::runtime_error &e)
    {
        return {false, {}, e.what()};
    }

    if (cube.getCube() != Constants::INITIAL_CUBE)
        return {false, {}, "Cube was not solved correctly"};

    auto raw = cube.getMoves();
    auto optimised = optimiseMoves(raw);

    std::vector<std::string> notation;
    for (const auto &[face, turns] : optimised)
        notation.push_back(moveToNotation(face, turns));

    return {true, notation, ""};
}
