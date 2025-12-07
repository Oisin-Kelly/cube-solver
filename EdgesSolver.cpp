#include "EdgesSolver.hpp"

EdgesSolver::EdgesSolver(Cube &cube) : cube(cube) {};

std::unordered_set<std::pair<Face, Face>, PairHash> EdgesSolver::getAlignedEdges() const
{
    std::unordered_set<std::pair<Face, Face>, PairHash> alignedFaces;

    if (cube[14] == FRONT && cube[21] == RIGHT)
        alignedFaces.insert({FRONT, RIGHT});
    if (cube[23] == RIGHT && cube[30] == BACK)
        alignedFaces.insert({RIGHT, BACK});
    if (cube[32] == BACK && cube[39] == LEFT)
        alignedFaces.insert({BACK, LEFT});
    if (cube[41] == LEFT && cube[12] == FRONT)
        alignedFaces.insert({LEFT, FRONT});

    return alignedFaces;
}

void EdgesSolver::solve()
{
    std::unordered_set<std::pair<Face, Face>, PairHash> alignedEdges = getAlignedEdges();

    while (alignedEdges.size() != 4)
    {
        break;
    }
}