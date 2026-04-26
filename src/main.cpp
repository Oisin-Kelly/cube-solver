#include "Cube.hpp"
#include "CubeSolverLib.hpp"
#include "Constants.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <unordered_map>

void printUsage(const char *programName)
{
    std::cout << "Usage: " << programName << " [options]\n"
              << "Options:\n"
              << "  -f, --file <path>    Load cube state from file\n"
              << "  -v, --verbose        Print detailed solving steps\n"
              << "  -h, --help           Show this help message\n";
}

bool loadCubeFromFile(const std::string &filename, std::array<Face, 54> &cubeState, std::array<char, 6> &faceColors)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file '" << filename << "'\n";
        return false;
    }

    std::string stickers;
    char c;
    while (file.get(c))
        if (!std::isspace(c)) stickers += c;

    if (stickers.size() != 54)
    {
        std::cerr << "Error: Expected 54 stickers, got " << stickers.size() << "\n";
        return false;
    }

    const Face faceOrder[] = {Face::UP, Face::FRONT, Face::RIGHT, Face::BACK, Face::LEFT, Face::DOWN};

    std::unordered_map<char, Face> colorToFace;
    for (int i = 0; i < 6; ++i)
    {
        char centre = stickers[Constants::CENTRE_INDICES[i]];
        if (colorToFace.count(centre))
        {
            std::cerr << "Error: Color '" << centre << "' is the centre of multiple faces\n";
            return false;
        }
        colorToFace[centre] = faceOrder[i];
        faceColors[i] = centre;
    }

    for (int i = 0; i < 54; ++i)
    {
        auto it = colorToFace.find(stickers[i]);
        if (it == colorToFace.end())
        {
            std::cerr << "Error: Unknown color '" << stickers[i] << "' at position " << i << "\n";
            return false;
        }
        cubeState[i] = it->second;
    }

    return true;
}

int main(int argc, char **argv)
{
    std::string filename;
    bool verbose = false;

    for (int i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--file") == 0)
        {
            if (i + 1 < argc)
                filename = argv[++i];
            else
            {
                std::cerr << "Error: --file requires an argument\n";
                return 1;
            }
        }
        else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0)
            verbose = true;
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

    std::array<Face, 54> cubeState;
    std::array<char, 6> faceColors = {'G', 'R', 'W', 'O', 'Y', 'B'};

    std::string loadFrom = filename.empty() ? "../example_cube.txt" : filename;
    if (filename.empty())
        std::cout << "No cube file provided, using fallback example_cube.txt\n";

    if (!loadCubeFromFile(loadFrom, cubeState, faceColors))
        return 1;

    if (verbose)
        std::cout << "Loaded cube from: " << loadFrom << "\n";

    Cube display(cubeState);
    display.setColorMap(faceColors);
    display.setVerbose(verbose);
    std::cout << "Initial cube state:\n";
    display.print();

    auto result = solveCube(cubeState);

    if (!result.success)
    {
        std::cerr << "Error: " << result.error << "\n";
        return 1;
    }

    display = Cube(Constants::INITIAL_CUBE);
    display.setColorMap(faceColors);
    std::cout << "Final cube state:\n";
    display.print();

    std::cout << "Cube solved successfully in " << result.moves.size() << " moves!\n";

    std::cout << "Moves:\n";
    for (const auto &move : result.moves)
        std::cout << move << " ";
    std::cout << "\n";

    return 0;
}
