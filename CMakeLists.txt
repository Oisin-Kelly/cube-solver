cmake_minimum_required(VERSION 3.10)
project(CubeSolver)

set(CMAKE_CXX_STANDARD 20)

include_directories(${PROJECT_SOURCE_DIR})

set(SOURCES
    main.cpp
    Cube.cpp
    CrossSolver.cpp
    CornerSolver.cpp
    EdgesSolver.cpp
    BottomCrossSolver.cpp
    BottomSolver.cpp
    Helpers.cpp
)

set(HEADERS
    Constants.hpp
    CrossSolver.hpp
    CornerSolver.hpp
    EdgesSolver.hpp
    BottomCrossSolver.hpp
    BottomSolver.hpp
    Cube.hpp
    Face.hpp
    Helpers.hpp
    Solver.hpp
    PairHash.hpp
)

add_executable(CubeSolver ${SOURCES} ${HEADERS})
