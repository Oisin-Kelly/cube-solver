#include "Cube.hpp"
#include "CornerSolver.hpp"
#include <iostream>
#include "CrossSolver.hpp"
#include "EdgesSolver.hpp"
#include "BottomSolver.hpp"

int main()
{
    Cube cube;

    CrossSolver crossSolver(cube);
    CornerSolver cornerSolver(cube);
    EdgesSolver edgeSolver(cube);
    BottomSolver bottomSolver(cube);

    crossSolver.solve();
    std::cout << "Cross Solved!" << std::endl;

    cornerSolver.solve();
    std::cout << "Corners solved!" << std::endl;

    edgeSolver.solve();
    std::cout << "Edges solved!" << std::endl;

    bottomSolver.solve();
    std::cout << "Bottom solved!" << std::endl;

    std::cout << std::endl;
    std::cout << "Cube solved!" << std::endl;
    std::cout << std::endl;

    std::cout << "Moves (unoptimised):" << std::endl;

    for (const std::string move : cube.getMoves())
        std::cout << move << " ";

    std::cout << std::endl;
    std::cout << "Total moves: " << cube.getMoves().size() << std::endl;

    return 0;
}
