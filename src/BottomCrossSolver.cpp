#include "BottomCrossSolver.hpp"
#include "Helpers.hpp"
#include "Constants.hpp"

void BottomCrossSolver::FLDLDF() const
{
    cube->rotateSide(Face::FRONT);
    cube->rotateSide(Face::LEFT);
    cube->rotateSide(Face::DOWN);
    cube->rotateSide(Face::LEFT, -1);
    cube->rotateSide(Face::DOWN, -1);
    cube->rotateSide(Face::FRONT, -1);
}

void BottomCrossSolver::RD2R_D_RD_R_(const Face edge_right) const
{
    cube->rotateSide(edge_right);
    cube->rotateSide(DOWN, 2);
    cube->rotateSide(edge_right, -1);
    cube->rotateSide(DOWN, -1);
    cube->rotateSide(edge_right);
    cube->rotateSide(DOWN, -1);
    cube->rotateSide(edge_right, -1);
}

void BottomCrossSolver::alignEdges() const
{
    const std::map<int, int> BOTTOM_EDGE_PAIRS = {
        {25, 16},
        {34, 25},
        {43, 34},
        {16, 43}};

    for (const auto pair : BOTTOM_EDGE_PAIRS)
    {
        if (cube->getCube()[pair.second] == Helpers::wrapDecrement(Face(cube->getCube()[pair.first])))
        {

            const Face face_left = Face(pair.first / 9);
            const Face edge_1 = cube->getCube()[pair.first];
            const Face edge_2 = cube->getCube()[pair.second];
            const auto N = edge_1 - face_left;
            cube->rotateSide(DOWN, N);

            if (hasAlignedCross())
                return;

            const Face edge_right = Helpers::wrapDecrement(edge_2);

            RD2R_D_RD_R_(edge_2);
            cube->rotateSide(DOWN, -1);

            break;
        }
    }

    if (!hasAlignedCross())
    {

        if (cube->getCube()[16] != FRONT && cube->getCube()[25] != RIGHT)
            cube->rotateSide(DOWN);

        for (auto const edge : Constants::BOTTOM_EDGE_MAP)
        {
            const Face edge_right = Helpers::wrapIncrement(Face(edge.first / 9));

            if (cube->getCube()[edge.first] == Face(edge.first / 9))
            {
                RD2R_D_RD_R_(edge_right);
                RD2R_D_RD_R_(Helpers::wrapDecrement(edge_right));
                cube->rotateSide(DOWN, -1);

                break;
            }
        }
    }
}

bool BottomCrossSolver::hasHorizontalLine() const
{
    return cube->getCube()[48] == DOWN && cube->getCube()[49] == DOWN && cube->getCube()[50] == DOWN;
}

bool BottomCrossSolver::hasVerticalLine() const
{
    return cube->getCube()[46] == DOWN && cube->getCube()[49] == DOWN && cube->getCube()[52] == DOWN;
}

bool BottomCrossSolver::hasR() const
{
    // even though the line may not have an 'R' shape on the bottom,
    // in order of solving the cross an 'R' comes before a line
    // R -> Line -> Cross
    if (hasCross() || hasLine())
        return true;

    if (cube->getCube()[46] == DOWN && cube->getCube()[50] == DOWN)
        return true;
    if (cube->getCube()[52] == DOWN && cube->getCube()[50] == DOWN)
        return true;
    if (cube->getCube()[48] == DOWN && cube->getCube()[52] == DOWN)
        return true;
    if (cube->getCube()[46] == DOWN && cube->getCube()[48] == DOWN)
        return true;

    return false;
}

bool BottomCrossSolver::hasAlignedCross() const
{
    return cube->getCube()[16] == FRONT && cube->getCube()[25] == RIGHT && cube->getCube()[34] == BACK && cube->getCube()[43] == LEFT;
}

BottomCrossSolver::BottomCrossSolver(Cube *cube) : cube(cube)
{
}

void BottomCrossSolver::solve()
{
    if (!hasR())
    {
        FLDLDF();
    }

    if (!hasLine())
    {
        if (cube->getCube()[46] == DOWN && cube->getCube()[50] == DOWN)
            cube->rotateSide(DOWN, -1);
        else if (cube->getCube()[48] == DOWN && cube->getCube()[52] == DOWN)
            cube->rotateSide(DOWN, 1);

        FLDLDF();

        if (cube->getCube()[46] == DOWN)
            cube->rotateSide(DOWN, 1);
    }

    if (hasAlignedCross())
        return;

    if (!hasCross())
    {
        if (cube->getCube()[46] == DOWN)
            cube->rotateSide(DOWN, 1);

        FLDLDF();
    }

    if (hasAlignedCross())
        return;

    alignEdges();
}
