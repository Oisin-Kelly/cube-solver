#include "Cube.hpp"
#include "CornerSolver.hpp"
#include <iostream>
#include "CrossSolver.hpp"

int main() {
    std::cout << "here 1\n";
    
    Cube mycube;
    mycube.print();

    CrossSolver myCrossSolve(mycube);
    CornerSolver mySolver(mycube);

    myCrossSolve.solve();
    std::cout << "Cross Solved!" << std::endl;
    mySolver.solve();

    return 0;
}