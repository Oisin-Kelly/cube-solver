#pragma once
#include "Cube.hpp"
#include "Solver.hpp"
#include <unordered_set>

class CrossSolver : public Solver
{
private:
    Cube *cube;

    void alignEdge(Face face, int N);
    std::unordered_set<Face> getAlignedFaces();
    bool hasAlignedEdge(Face side);

public:
    explicit CrossSolver(Cube *cube);

    void solve() override;
};