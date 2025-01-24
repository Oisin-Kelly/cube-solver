#pragma once
#include "Cube.hpp"
#include "Solver.hpp"
#include <unordered_set>

class CrossSolver: public Solver {
    private:
        Cube& cube;

        void alignEdge(Face face, int N);
        const std::unordered_set<Face> get_aligned_faces() const;
        bool hasAlignedEdge(Face side);

    public:
        explicit CrossSolver(Cube& cube);

        void solve() override;
};