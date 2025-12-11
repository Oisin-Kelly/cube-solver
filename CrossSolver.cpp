#include "CrossSolver.hpp"
#include "Constants.hpp"
#include "Helpers.hpp"
#include <unistd.h>
#include <ostream>
#include <iostream>

CrossSolver::CrossSolver(Cube &cube) : cube(cube) {};

void CrossSolver::alignEdge(Face face, int N)
{
    if (N == 1)
    {
        cube.rotateSide(Face::UP, -1);
        cube.rotateSide(Helpers::wrapIncrement(face));
        cube.rotateSide(Face::UP);
    }
    else
    {
        cube.rotateSide(Face::UP);
        cube.rotateSide(Helpers::wrapDecrement(face), -1);
        cube.rotateSide(Face::UP, -1);
    }
}

bool CrossSolver::hasAlignedEdge(Face side)
{
    const uint8_t t_index = side * 9 + 1;

    return cube[t_index] == side && cube[Constants::EDGE_MAP.at(t_index)] == 0;
}

std::unordered_set<Face> CrossSolver::getAlignedFaces()
{
    std::unordered_set<Face> alignedFaces;

    if (cube[7] == UP && cube[10] == FRONT)
        alignedFaces.insert(FRONT);
    if (cube[5] == UP && cube[19] == RIGHT)
        alignedFaces.insert(RIGHT);
    if (cube[1] == UP && cube[28] == BACK)
        alignedFaces.insert(BACK);
    if (cube[3] == UP && cube[37] == LEFT)
        alignedFaces.insert(LEFT);

    return alignedFaces;
}

void CrossSolver::solve()
{
    std::unordered_set<Face> alignedFaces = getAlignedFaces();

     while (alignedFaces.size() != 4)
    {
        for (auto const edge : Constants::EDGE_MAP)
        {
            if (cube[edge.first] != UP)
                continue;

            const Face c_edge = cube[edge.second];     // edge number for colored side of edge; 1 .. 4
            const uint8_t t_index = c_edge * 9 + 1;    // top index of edge for eg. If c_edge == 1 then the top index is 10
            const Face c_side = Face(edge.second / 9); // the face where the colored edge lies; 0 ... 5
            const Face green_side = Face(edge.first / 9);

            if (hasAlignedEdge(c_edge))
            {
                alignedFaces.insert(c_edge);

                if (alignedFaces.size() == 4)
                    break;

                continue;
            }

            // if coloured side of edge on horizontal plane
            if (FRONT <= c_edge && c_edge <= LEFT && 9 * c_edge + 3 <= edge.second && (9 * (c_edge + 1)) - 1 >= edge.second)
            {
                do
                    cube.rotateSide(c_edge);
                while (cube[t_index] != c_edge && cube[Constants::EDGE_MAP.at(t_index)] != 0);

                break;
            }

            if (c_side == 0)
            {
                const int N = Helpers::getTurns(c_edge, green_side);

                switch (N)
                {
                case 0:
                    cube.rotateSide(Face::UP);
                    cube.rotateSide(Helpers::wrapDecrement(c_edge));
                    cube.rotateSide(Face::UP, -1);
                    cube.rotateSide(c_edge);

                    break;

                case 1:
                case -1:
                    cube.rotateSide(green_side, -N);
                    cube.rotateSide(c_edge, -N);

                    break;

                case 2:
                    cube.rotateSide(Face::UP, -1);
                    cube.rotateSide(Helpers::wrapDecrement(c_edge));
                    cube.rotateSide(Face::UP);
                    cube.rotateSide(c_edge);

                    break;
                }

                break;
            }
            else if (c_side == 5)
            {
                const int N = Helpers::getTurns(c_edge, green_side);

                cube.rotateSide(Face::DOWN, -N);
                cube.rotateSide(c_edge, -1);
                cube.rotateSide(Face::UP, -1);
                cube.rotateSide(Helpers::wrapIncrement(c_edge));
                cube.rotateSide(Face::UP);

                break;
            }

            const int N = Helpers::getTurns(c_edge, c_side);

            if (N == -1 || N == 1)
            {
                if (Helpers::get_row(edge.second) == 0)
                {
                    cube.rotateSide(c_side, -N);
                    alignEdge(c_edge, N);
                }
                else if (Helpers::get_row(edge.second) == 1)
                {
                    if (N == 1 && Helpers::get_column(edge.second) == 2)
                    {
                        cube.rotateSide(c_side, -2);
                        cube.rotateSide(Face::UP, -1);
                        cube.rotateSide(c_side);
                        cube.rotateSide(Face::UP);
                        cube.rotateSide(c_side);

                        break;
                    }
                    else if (N == -1 && Helpers::get_column(edge.second) == 0)
                    {
                        cube.rotateSide(c_side, 2);
                        cube.rotateSide(Face::UP);
                        cube.rotateSide(c_side, -1);
                        cube.rotateSide(Face::UP, -1);
                        cube.rotateSide(c_side, -1);

                        break;
                    }
                    else
                    {
                        alignEdge(c_edge, N);
                    }
                }
                else
                {
                    cube.rotateSide(Face::DOWN, -N);
                    cube.rotateSide(c_edge, 2);

                    break;
                }
            }
            else if (N == 2)
            {
                if (Helpers::get_row(edge.second) == 0)
                {
                    if (alignedFaces.size() == 0)
                    {
                        cube.rotateSide(Face::UP, 2);

                        break;
                    }

                    cube.rotateSide(c_side, 2);
                }
                else if (Helpers::get_row(edge.second) == 1)
                {
                    const int sideRotation = Helpers::get_column(edge.second) == 0 ? -1 : 1;

                    cube.rotateSide(c_side, sideRotation);

                    cube.rotateSide(Face::DOWN, 2);
                    cube.rotateSide(c_edge, 2);
                    cube.rotateSide(c_side, -sideRotation);
                }
                else
                {
                    cube.rotateSide(Face::DOWN, 2);
                    cube.rotateSide(c_edge, 2);
                }

                break;
            }
        }
    }
}