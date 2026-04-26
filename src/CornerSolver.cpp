#include "CornerSolver.hpp"
#include "Constants.hpp"
#include "Helpers.hpp"

CornerSolver::CornerSolver(Cube *cube) : cube(cube) {};

std::unordered_set<std::pair<Face, Face>, PairHash> CornerSolver::getAlignedCorners() const
{
    std::unordered_set<std::pair<Face, Face>, PairHash> alignedCorners;

    if (cube->getCube()[11] == FRONT && cube->getCube()[18] == RIGHT)
        alignedCorners.insert({FRONT, RIGHT});
    if (cube->getCube()[20] == RIGHT && cube->getCube()[27] == BACK)
        alignedCorners.insert({RIGHT, BACK});
    if (cube->getCube()[29] == BACK && cube->getCube()[36] == LEFT)
        alignedCorners.insert({BACK, LEFT});
    if (cube->getCube()[38] == LEFT && cube->getCube()[9] == FRONT)
        alignedCorners.insert({LEFT, FRONT});

    return alignedCorners;
}

void CornerSolver::solve()
{
    std::unordered_set<std::pair<Face, Face>, PairHash> alignedCorners = getAlignedCorners();

    while (alignedCorners.size() != 4)
    {
        for (int i = 0; i < Constants::CORNERS.size(); ++i)
        {
            const std::tuple<int, int, int> corner = Constants::CORNERS[i];

            const int topEdge = std::get<0>(corner);
            const int leftEdge = std::get<1>(corner);
            const int rightEdge = std::get<2>(corner);

            if (cube->getCube()[topEdge] != UP && cube->getCube()[leftEdge] != UP && cube->getCube()[rightEdge] != UP)
                continue;

            const Face face1 = cube->getCube()[leftEdge];
            const Face face2 = cube->getCube()[rightEdge];

            int greenEdge = topEdge;
            greenEdge = cube->getCube()[leftEdge] == UP ? leftEdge : greenEdge;
            greenEdge = cube->getCube()[rightEdge] == UP ? rightEdge : greenEdge;

            if (greenEdge < 9) // its on top
            {
                if (face1 == cube->getCube()[leftEdge + 2])
                { // its already in its spot
                    alignedCorners.insert({face1, face2});

                    if (alignedCorners.size() == 4)
                        break;

                    continue;
                }
                else
                {
                    cube->rotateSide(leftEdge / 9);

                    int N = Helpers::getTurns(Helpers::wrapIncrement(Face(rightEdge / 9)), face2);

                    cube->rotateSide(DOWN);

                    cube->rotateSide(leftEdge / 9, -1);
                    cube->rotateSide(DOWN, N + 1);
                    cube->rotateSide(face1);
                    cube->rotateSide(DOWN, -1);
                    cube->rotateSide(face1, -1);

                    break;
                }
            }
            else if (greenEdge >= 9 && greenEdge < 45)
            {
                const uint8_t column = Helpers::get_column(greenEdge);
                const uint8_t row = Helpers::get_row(greenEdge);
                std::tuple<int, int, int> bottomCorner = corner;

                if (row == 0)
                {
                    if (column == 0)
                    { // left
                        cube->rotateSide(Face(greenEdge / 9), -1);
                        cube->rotateSide(DOWN, -1);
                        cube->rotateSide(Face(greenEdge / 9));

                        bottomCorner = Constants::CORNERS[Helpers::wrapDecrement(Face(i + 1)) - 1 + 4];
                    }
                    else
                    { // right
                        cube->rotateSide(Face(greenEdge / 9));
                        cube->rotateSide(DOWN);
                        cube->rotateSide(Face(greenEdge / 9), -1);

                        bottomCorner = Constants::CORNERS[Helpers::wrapIncrement(Face(i + 1)) - 1 + 4];
                    }
                }

                const int bottomEdge = std::get<0>(bottomCorner);
                const int bottomLeftEdge = std::get<1>(bottomCorner);
                const int bottomRightEdge = std::get<2>(bottomCorner);

                const Face bottomFace = cube->getCube()[bottomEdge];
                const Face bottomFaceLeft = cube->getCube()[bottomLeftEdge];   // Fixed: was using leftEdge
                const Face bottomFaceRight = cube->getCube()[bottomRightEdge]; // Fixed: was using rightEdge

                if (column == 0)
                {
                    int N = Helpers::getTurns(Face(bottomLeftEdge / 9), Helpers::wrapIncrement(bottomFace));

                    cube->rotateSide(DOWN, N);
                    cube->rotateSide(bottomFaceRight);
                    cube->rotateSide(DOWN, -1);
                    cube->rotateSide(bottomFaceRight, -1);
                }
                else
                {
                    int N = Helpers::getTurns(Face(bottomRightEdge / 9), Helpers::wrapDecrement(bottomFace));

                    cube->rotateSide(DOWN, N);
                    cube->rotateSide(bottomFaceLeft, -1);
                    cube->rotateSide(DOWN);
                    cube->rotateSide(bottomFaceLeft);
                }

                break;
            }
            else
            {
                const int N = Helpers::getTurns(Helpers::wrapDecrement(Face(leftEdge / 9)), face1);

                cube->rotateSide(DOWN, N);
                cube->rotateSide(face1);
                cube->rotateSide(DOWN, -1);
                cube->rotateSide(face1, -1);
                cube->rotateSide(DOWN);

                cube->rotateSide(face2, -1);
                cube->rotateSide(DOWN);
                cube->rotateSide(face2);

                break;
            }
        }
    }
}