#pragma once
#include "Cube.hpp"
#include "Solver.hpp"

class BottomCrossSolver : Solver
{
private:
    Cube *cube;

    void FLDLDF() const;
    void RD2R_D_RD_R_(const Face edge_right) const;
    void alignEdges() const;

    bool hasHorizontalLine() const;
    bool hasVerticalLine() const;

    bool hasR() const;
    bool hasLine() const { return hasHorizontalLine() || hasVerticalLine(); };
    bool hasCross() const { return hasHorizontalLine() && hasVerticalLine(); };
    bool hasAlignedCross() const;

public:
    explicit BottomCrossSolver(Cube *cube);

    void solve() override;
};