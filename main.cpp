#include "Cube.hpp"
#include "CornerSolver.hpp"
#include <iostream>
#include <map>
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

    cube.print();

    Cube cube2;

    int i = 0;

    for (auto const move : cube.getMoves())
    {
        cube2.rotateSide(std::get<0>(move), std::get<1>(move));

        // std::cout << i++ << ": rotate " << (int)std::get<0>(move) << " " << std::get<1>(move) << " moves:" << std::endl;
        if (std::get<0>(move) == 0)
            std::cout << "[G" << " " << std::get<1>(move);
        if (std::get<0>(move) == 1)
            std::cout << "[R" << " " << std::get<1>(move);
        if (std::get<0>(move) == 2)
            std::cout << "[W" << " " << std::get<1>(move);
        if (std::get<0>(move) == 3)
            std::cout << "[O" << " " << std::get<1>(move);
        if (std::get<0>(move) == 4)
            std::cout << "[Y" << " " << std::get<1>(move);
        if (std::get<0>(move) == 5)
            std::cout << "[B" << " " << std::get<1>(move);

        std::cout << "] ";
    }

    std::cout << cube.getMoves().size();

    // cube2.print();

    return 0;
}
