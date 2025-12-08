#pragma once
#include "Cube.hpp"
#include "Solver.hpp"
#include <unordered_set>
#include "PairHash.hpp"

class EdgesSolver : Solver
{
private:
    Cube &cube;
    std::unordered_set<std::pair<Face, Face>, PairHash> getAlignedEdges() const;

public:
    explicit EdgesSolver(Cube &cube);

    void solve() override;
};