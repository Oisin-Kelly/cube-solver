#include "Cube.hpp"
#include "CornerSolver.hpp"
#include <iostream>
#include "CrossSolver.hpp"
#include "EdgesSolver.hpp"

int main()
{
    Cube mycube;

    CrossSolver myCrossSolve(mycube);
    CornerSolver mySolver(mycube);
    EdgesSolver myEdgeSolver(mycube);

    myCrossSolve.solve();
    std::cout << "Cross Solved!" << std::endl;

    mySolver.solve();
    std::cout << "Corners solved!" << std::endl;

    myEdgeSolver.solve();
    std::cout << "Edges solved!" << std::endl;

    std::cout << std::endl;

    std::cout << "Moves (unoptimised):" << std::endl;

    for (const std::string move : mycube.getMoves())
        std::cout << move << " ";

    std::cout << std::endl;
    std::cout << "Total moves: " << mycube.getMoves().size() << std::endl;

    return 0;
}
