cmake_minimum_required(VERSION 3.10)
project(CubeSolver)

set(CMAKE_CXX_STANDARD 20)

find_package(httplib CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

add_library(cube_solver_lib STATIC
    src/Cube.cpp
    src/Helpers.cpp
    src/CrossSolver.cpp
    src/CornerSolver.cpp
    src/EdgesSolver.cpp
    src/BottomCrossSolver.cpp
    src/BottomSolver.cpp
    src/CubeSolverLib.cpp
)
target_include_directories(cube_solver_lib PUBLIC ${PROJECT_SOURCE_DIR}/src)

add_executable(CubeSolver src/main.cpp)
target_link_libraries(CubeSolver PRIVATE cube_solver_lib)

add_executable(CubeSolverServer src/server.cpp)
target_link_libraries(CubeSolverServer PRIVATE cube_solver_lib nlohmann_json::nlohmann_json httplib::httplib fmt::fmt)

enable_testing()
add_executable(CubeSolverTests
    tests/test_optimise.cpp
    tests/test_solve.cpp
)
target_link_libraries(CubeSolverTests PRIVATE cube_solver_lib GTest::gtest GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(CubeSolverTests)
