#include "Cube.hpp"
#include "CrossSolver.hpp"
int main() {
    Cube mycube;
    
    mycube.print();

    CrossSolver mySolver(mycube);

    mySolver.solve();

    return 0;
}