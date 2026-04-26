#pragma once
#include "Cube.hpp"
#include "Solver.hpp"
#include <unordered_set>
#include "PairHash.hpp"

class CornerSolver : Solver
{
private:
    Cube *cube;

    std::unordered_set<std::pair<Face, Face>, PairHash> getAlignedCorners() const;

public:
    explicit CornerSolver(Cube *cube);

    void solve() override;
};