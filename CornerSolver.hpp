#pragma once
#include "Cube.hpp"
#include "Solver.hpp"

class CornerSolver: public Solver {
    private:
        Cube& cube;
    public:
        explicit CornerSolver(Cube& cube);

        void solve() override;
};