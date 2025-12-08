#include "Cube.hpp"
#include "CornerSolver.hpp"
#include <iostream>
#include "CrossSolver.hpp"
#include "EdgesSolver.hpp"

int main()
{
    std::cout << "here 1\n";

    Cube mycube;
    mycube.print();

    CrossSolver myCrossSolve(mycube);
    CornerSolver mySolver(mycube);
    EdgesSolver myEdgeSolver(mycube);

    myCrossSolve.solve();
    std::cout << "Cross Solved!" << std::endl;
    mySolver.solve();
    std::cout << "Corners solved!" << std::endl;
    myEdgeSolver.solve();
    std::cout << "Edges solved!" << std::endl;

    return 0;
}