#pragma once
#include "Cube.hpp"
#include "Solver.hpp"
#include <unordered_set>

struct PairHash {
    template <typename T1, typename T2>
    std::size_t operator()(const std::pair<T1, T2>& pair) const {
        return pair.first ^ pair.second;
    }
};

class CornerSolver : Solver {
    private:
        Cube& cube;

        std::unordered_set<std::pair<Face, Face>, PairHash> getAlignedCorners();
    public:
        explicit CornerSolver(Cube& cube);

        void solve() override;
        
};