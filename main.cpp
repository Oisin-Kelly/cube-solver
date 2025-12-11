#include "Cube.hpp"
#include "CornerSolver.hpp"
#include "CrossSolver.hpp"
#include "EdgesSolver.hpp"
#include "BottomSolver.hpp"
#include "Constants.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>

void printUsage(const char *programName)
{
    std::cout << "Usage: " << programName << " [options]\n"
              << "Options:\n"
              << "  -f, --file <path>    Load cube state from file\n"
              << "  -v, --verbose        Print detailed solving steps\n"
              << "  -p, --print          Print cube state before and after solving\n"
              << "  -h, --help           Show this help message\n";
}

const Face charToFace(const char c)
{
    switch (c)
    {
    case 'G':
        return Face::UP;
    case 'R':
        return Face::FRONT;
    case 'W':
        return Face::RIGHT;
    case 'O':
        return Face::BACK;
    case 'Y':
        return Face::LEFT;
    case 'B':
        return Face::DOWN;
    default:
        throw std::invalid_argument(std::string("Invalid color: ") + c);
    }
}

const char faceToChar(const Face f)
{
    switch (f)
    {
    case 0:
        return 'G';
    case 1:
        return 'R';
    case 2:
        return 'W';
    case 3:
        return 'O';
    case 4:
        return 'Y';
    case 5:
        return 'B';
    }
}

bool loadCubeFromFile(const std::string filename, std::array<Face, 54> &cubeState)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file '" << filename << "'\n";
        return false;
    }

    int index = 0;
    std::string line;
    while (std::getline(file, line) && index < 54)
    {
        std::istringstream iss(line);
        char c;
        while (iss >> c && index < 54)
        {
            try
            {
                cubeState[index++] = charToFace(c);
            }
            catch (const std::invalid_argument e)
            {
                std::cerr << "Error: " << e.what() << " at position " << index << "\n";
                return false;
            }
        }
    }

    if (index != 54)
    {
        std::cerr << "Error: Expected 54 cube stickers, got " << index << "\n";
        return false;
    }

    std::array<int, 6> colorCounts = {0, 0, 0, 0, 0, 0};
    for (const auto face : cubeState)
    {
        colorCounts[static_cast<int>(face)]++;
    }

    for (int i = 0; i < 6; ++i)
    {
        if (colorCounts[i] != 9)
        {
            std::cerr << "Error: Color " << static_cast<char>("GRWOBY"[i])
                      << " appears " << colorCounts[i] << " times, expected 9\n";
            return false;
        }
    }

    return true;
}

void printMoves(const std::vector<std::tuple<Face, int>> moves)
{
    std::cout << "Moves:\n";
    for (const auto move : moves)
        std::cout << "[" << faceToChar(std::get<0>(move)) << " " << std::get<1>(move) << "] ";
    std::cout << "\n";
}

int main(int argc, char **argv)
{
    std::string filename;
    bool verbose = false;
    bool printCube = false;

    for (int i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--file") == 0)
        {
            if (i + 1 < argc)
            {
                filename = argv[++i];
            }
            else
            {
                std::cerr << "Error: --file requires an argument \n";
                return 1;
            }
        }
        else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0)
        {
            verbose = true;
        }
        else if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--print") == 0)
        {
            printCube = true;
        }
        else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
        {
            printUsage(argv[0]);
            return 0;
        }
        else
        {
            std::cerr << "Error: Unknown option '" << argv[i] << "'\n";
            printUsage(argv[0]);
            return 1;
        }
    }

    Cube cube;

    if (!filename.empty())
    {
        std::array<Face, 54> cubeState;
        if (!loadCubeFromFile(filename, cubeState))
        {
            return 1;
        }

        cube = Cube(cubeState);

        if (verbose)
        {
            std::cout << "Loaded cube from: " << filename << "\n";
        }
    }
    else
    {
        std::cout << "No cube file inputted, using fallback example_cube.txt\n";
        std::array<Face, 54> cubeState;

        if (!loadCubeFromFile("../example_cube.txt", cubeState))
        {
            return 1;
        }

        cube = Cube(cubeState);

        if (verbose)
        {
            std::cout << "Loaded cube from: example_cube.txt\n";
        }
    }

    if (printCube)
    {
        std::cout << "Initial cube state:\n";
        cube.print();
        std::cout << "\n";
    }

    CrossSolver crossSolver(&cube);
    CornerSolver cornerSolver(&cube);
    EdgesSolver edgeSolver(&cube);
    BottomSolver bottomSolver(&cube);

    if (verbose)
        std::cout << "Solving cross...\n";
    crossSolver.solve();
    if (verbose)
        std::cout << "Cross solved!\n";

    if (verbose)
        std::cout << "Solving corners...\n";
    cornerSolver.solve();
    if (verbose)
        std::cout << "Corners solved!\n";

    if (verbose)
        std::cout << "Solving edges...\n";
    edgeSolver.solve();
    if (verbose)
        std::cout << "Edges solved!\n";

    if (verbose)
        std::cout << "Solving bottom layer...\n";
    bottomSolver.solve();
    if (verbose)
        std::cout << "Bottom layer solved!\n";

    if (printCube)
    {
        std::cout << "Final cube state:\n";
        cube.print();
        std::cout << "\n";
    }

    if (cube.getCube() == Constants::INITIAL_CUBE)
    {
        std::cout << "Cube solved successfully in " << cube.getMoves().size() << " moves!\n";
        printMoves(cube.getMoves());
    }
    else
    {
        std::cerr << "Error: Cube was not solved correctly!\n";
        return 1;
    }

    return 0;
}