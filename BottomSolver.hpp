#pragma once
#include "Cube.hpp"
#include "Solver.hpp"
#include "BottomCrossSolver.hpp"

class BottomSolver : Solver
{
private:
    Cube *cube;

    void L_DRD_LDR_D_() { L_DRD_LDR_D_(Face::LEFT, Face::RIGHT); }
    void L_DRD_LDR_D_(const Face left, const Face right);
    void RD2R_D_RD_R_L_D2LDL_DL() { RD2R_D_RD_R_L_D2LDL_DL(Face::LEFT, Face::RIGHT); }
    void RD2R_D_RD_R_L_D2LDL_DL(const Face left, const Face right);

    bool hasCorrectCorner(std::tuple<int, int, int> corner) const;
    bool hasCorrectOrientation(std::tuple<int, int, int> corner) const;
    int getNumberCorrectCorners() const;
    int getNumberCorrectOrientationCorners() const;
    int getBottomLeftIndexOfCorrectCorner() const;

    BottomCrossSolver crossSolver;

public:
    explicit BottomSolver(Cube *cube);

    void solve() override;
};