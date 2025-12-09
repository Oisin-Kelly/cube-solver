#pragma once
#include "Cube.hpp"
#include "Solver.hpp"
#include "BottomCrossSolver.hpp"

class BottomSolver : Solver
{
private:
    Cube &cube;

    BottomCrossSolver crossSolver;

public:
    explicit BottomSolver(Cube &cube);

    void solve() override;
};