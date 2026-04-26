#include "EdgesSolver.hpp"
#include "Constants.hpp"
#include "Helpers.hpp"

EdgesSolver::EdgesSolver(Cube *cube) : cube(cube) {};

std::unordered_set<std::pair<Face, Face>, PairHash> EdgesSolver::getAlignedEdges() const
{
    std::unordered_set<std::pair<Face, Face>, PairHash> alignedFaces;

    if (cube->getCube()[14] == FRONT && cube->getCube()[21] == RIGHT)
        alignedFaces.insert({FRONT, RIGHT});
    if (cube->getCube()[23] == RIGHT && cube->getCube()[30] == BACK)
        alignedFaces.insert({RIGHT, BACK});
    if (cube->getCube()[32] == BACK && cube->getCube()[39] == LEFT)
        alignedFaces.insert({BACK, LEFT});
    if (cube->getCube()[41] == LEFT && cube->getCube()[12] == FRONT)
        alignedFaces.insert({LEFT, FRONT});

    return alignedFaces;
}

void EdgesSolver::solve()
{
    std::unordered_set<std::pair<Face, Face>, PairHash> alignedEdges = getAlignedEdges();

    while (alignedEdges.size() != 4)
    {
        // insert pairs on bottom that don't contain any of the DOWN colour

        for (auto const edge : Constants::BOTTOM_EDGE_MAP)
        {
            if (cube->getCube()[edge.first] == Face::DOWN || cube->getCube()[edge.second] == Face::DOWN)
                continue;

            const Face color_1 = cube->getCube()[edge.first];  // side, bottom colour
            const Face color_2 = cube->getCube()[edge.second]; // colour on bottom
            const Face face_1 = Face(edge.first / 9);          // colour of Face where color_1 lies

            const int turns = Helpers::getTurns(face_1, color_1); // 2
            cube->rotateSide(Face::DOWN, turns);

            const int N = Helpers::getTurns(color_1, color_2);

            cube->rotateSide(DOWN, -N);
            cube->rotateSide(color_2, -N);
            cube->rotateSide(DOWN, N);
            cube->rotateSide(color_2, N);
            cube->rotateSide(DOWN, N);
            cube->rotateSide(color_1, N);
            cube->rotateSide(DOWN, -N);
            cube->rotateSide(color_1, -N);
        }

        if (getAlignedEdges().size() == 4)
        {

            return;
        }

        // insert pairs on the middle row

        for (auto const edge : Constants::MIDDLE_EDGE_MAP)
        {
            const Face face_1 = Face(edge.first / 9);
            const Face face_2 = Face(edge.second / 9);
            const Face edge_1 = cube->getCube()[edge.first];
            const Face edge_2 = cube->getCube()[edge.second];

            if (edge_1 == face_1 && edge_2 == face_2)
                continue;

            if (edge_1 == DOWN || edge_2 == DOWN)
                continue;

            // edge is in wrong middle slot - eject it to bottom layer first
            const int N = Helpers::getTurns(face_1, face_2);

            cube->rotateSide(DOWN, -N);
            cube->rotateSide(face_2, -N);
            cube->rotateSide(DOWN, N);
            cube->rotateSide(face_2, N);
            cube->rotateSide(DOWN, N);
            cube->rotateSide(face_1, N);
            cube->rotateSide(DOWN, -N);
            cube->rotateSide(face_1, -N);

            break;
        }

        alignedEdges = getAlignedEdges();
    }
}