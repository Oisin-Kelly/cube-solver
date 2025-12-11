#include "BottomSolver.hpp"
#include "Constants.hpp"
#include "Helpers.hpp"
#include <iostream>
#include <unordered_set>

void BottomSolver::L_DRD_LDR_D_(const Face left, const Face right)
{
    cube.rotateSide(left, -1);
    cube.rotateSide(Face::DOWN);
    cube.rotateSide(right);
    cube.rotateSide(Face::DOWN, -1);

    cube.rotateSide(left);
    cube.rotateSide(Face::DOWN);
    cube.rotateSide(right, -1);
    cube.rotateSide(Face::DOWN, -1);
}

void BottomSolver::RD2R_D_RD_R_L_D2LDL_DL(const Face left, const Face right)
{
    cube.rotateSide(right);
    cube.rotateSide(Face::DOWN, 2);
    cube.rotateSide(right, -1);
    cube.rotateSide(Face::DOWN, -1);
    cube.rotateSide(right);
    cube.rotateSide(Face::DOWN, -1);
    cube.rotateSide(right, -1);

    cube.rotateSide(left, -1);
    cube.rotateSide(Face::DOWN, 2);
    cube.rotateSide(left);
    cube.rotateSide(Face::DOWN);
    cube.rotateSide(left, -1);
    cube.rotateSide(Face::DOWN);
    cube.rotateSide(left);
}

bool BottomSolver::hasCorrectCorner(std::tuple<int, int, int> corner) const
{
    const int idx_1 = std::get<0>(corner);
    const int idx_2 = std::get<1>(corner);
    const int idx_3 = std::get<2>(corner);

    const Face corner_1 = cube[idx_1];
    const Face corner_2 = cube[idx_2];
    const Face corner_3 = cube[idx_3];

    const Face face_1 = Face(idx_1 / 9);
    const Face face_2 = Face(idx_2 / 9);
    const Face face_3 = Face(idx_3 / 9);

    std::unordered_set<Face> cornerColors = {corner_1, corner_2, corner_3};
    std::unordered_set<Face> faceColors = {face_1, face_2, face_3};

    return cornerColors == faceColors;
}

bool BottomSolver::hasCorrectOrientation(std::tuple<int, int, int> corner) const
{
    const int idx_1 = std::get<0>(corner);
    const int idx_2 = std::get<1>(corner);
    const int idx_3 = std::get<2>(corner);

    const Face corner_1 = cube[idx_1];
    const Face corner_2 = cube[idx_2];
    const Face corner_3 = cube[idx_3];

    const Face face_1 = Face(idx_1 / 9);
    const Face face_2 = Face(idx_2 / 9);
    const Face face_3 = Face(idx_3 / 9);

    return (corner_1 == face_1) && (corner_2 == face_2) && (corner_3 == face_3);
}

int BottomSolver::getNumberCorrectOrientationCorners() const
{
    int numCorrectCorners = 0;
    for (auto const corner : Constants::BOTTOM_CORNERS)
    {
        if (hasCorrectOrientation(corner))
            numCorrectCorners++;
    }
    return numCorrectCorners;
}

int BottomSolver::getNumberCorrectCorners() const
{
    int numCorrectCorners = 0;
    for (auto const corner : Constants::BOTTOM_CORNERS)
    {
        if (hasCorrectCorner(corner))
            numCorrectCorners++;
    }
    return numCorrectCorners;
}

int BottomSolver::getBottomLeftIndexOfCorrectCorner() const
{
    // assuming there is only one corner piece in its correct corner position

    for (auto const corner : Constants::BOTTOM_CORNERS)
    {
        if (hasCorrectCorner(corner))
            return std::get<1>(corner);
    }

    return 0;
}

BottomSolver::BottomSolver(Cube &cube) : cube(cube), crossSolver(cube) {};

void BottomSolver::solve()
{
    // align cross with edges on bottom
    crossSolver.solve();

    // need to solve corners
    int numCorrectCorners = getNumberCorrectCorners();

    while (numCorrectCorners != 4)
    {
        if (numCorrectCorners == 1)
        {
            for (auto const corner : Constants::BOTTOM_CORNERS)
            {
                if (hasCorrectCorner(corner))
                {
                    const auto idx = std::get<1>(corner);
                    const Face left = Helpers::wrapIncrement(Face(idx / 9));
                    const Face right = Helpers::wrapDecrement(Face(idx / 9));

                    L_DRD_LDR_D_(left, right);
                }
            }
        }
        else
        {
            L_DRD_LDR_D_();
        }

        numCorrectCorners = getNumberCorrectCorners();
    }

    // all 4 corners now in correct position

    numCorrectCorners = getNumberCorrectOrientationCorners();

    if (numCorrectCorners == 4)
        return;

    while (numCorrectCorners != 4)
    {

        if (numCorrectCorners == 0)
        {
            RD2R_D_RD_R_L_D2LDL_DL();
        }
        else if (numCorrectCorners == 2)
        {
            bool solved = false;
            // get side where both bottom corners are incorrectly oriented
            for (int i = 1; i < 5; ++i)
            {
                if (cube[i * 9 + 6] != Face(i) && cube[i * 9 + 8] != Face(i))
                {
                    while (getNumberCorrectOrientationCorners() != 4)
                    {

                        const auto right = Face(i);
                        const auto left = Helpers::wrapDecrement(Helpers::wrapDecrement(right));

                        RD2R_D_RD_R_L_D2LDL_DL(left, right);
                    }

                    solved = true;
                    break;
                }
            }

            if (solved)
                break;

            RD2R_D_RD_R_L_D2LDL_DL();
        }
        else if (numCorrectCorners == 1)
        {
            for (int i = 1; i <= 4; ++i)
            {
                if (cube[i * 9 + 6] != Face(i) && cube[i * 9 + 8] != Face(i))
                {
                    const auto right = Face(i);
                    const auto left = Helpers::wrapDecrement(Helpers::wrapDecrement(right));

                    RD2R_D_RD_R_L_D2LDL_DL(left, right);

                    break;
                }
            }
        }

        numCorrectCorners = getNumberCorrectOrientationCorners();
    }
}