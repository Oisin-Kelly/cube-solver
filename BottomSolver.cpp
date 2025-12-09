#include "BottomSolver.hpp"

BottomSolver::BottomSolver(Cube &cube) : cube(cube), crossSolver(cube) {};

void BottomSolver::solve()
{
    crossSolver.solve();

    // corners
    // find, if any, a corner in its right position, regardless of orientation
}