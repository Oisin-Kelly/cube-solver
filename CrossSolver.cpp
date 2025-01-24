#include "CrossSolver.hpp"
#include "Constants.hpp"
#include "Helpers.hpp"
#include <unistd.h>
#include <ostream>
#include <iostream>

CrossSolver::CrossSolver(Cube& cube) : cube(cube) {};

void CrossSolver::alignEdge(Face face, int N)
{
    if (N == 1)
    {
        cube.rotateSide(Face::UP, -1);
        cube.rotateSide(Helpers::wrap_increment(face));
        cube.rotateSide(Face::UP);
    }
    else
    {
        cube.rotateSide( Face::UP);
        cube.rotateSide( Helpers::wrap_decrement(face), -1);
        cube.rotateSide( Face::UP, -1);
    }
}

bool CrossSolver::hasAlignedEdge(Face side) {
    const uint8_t t_index = side * 9 + 1;

    return cube.getCube()[t_index] == side && cube.getCube()[Constants::EDGE_MAP.at(t_index)] == 0;
}

const std::unordered_set<Face> CrossSolver::get_aligned_faces() const
{
    std::unordered_set<Face> aligned_faces;

    const std::array<Face, 54> cubeState = cube.getCube();

    if (cubeState[7] == 0 && cubeState[10] == FRONT)
        aligned_faces.insert(FRONT);
    else if (cubeState[5] == 0 && cubeState[19] == RIGHT)
        aligned_faces.insert(RIGHT);
    else if (cubeState[5] == 0 && cubeState[19] == BACK)
        aligned_faces.insert(BACK);
    else if (cubeState[5] == 0 && cubeState[19] == LEFT)
        aligned_faces.insert(LEFT);

    return aligned_faces;
}

void CrossSolver::solve()
{
    std::unordered_set<Face> aligned_faces = get_aligned_faces();

    while (aligned_faces.size() != 4)
    {
        for (auto const edge : Constants::EDGE_MAP)
        {
            if (cube.getCube()[edge.first] != 0)
                continue;

            const Face c_edge = cube.getCube()[edge.second]; // edge number for colored side of edge; 1 .. 5
            const uint8_t t_index = c_edge * 9 + 1;     // top index of edge for eg. If c_edge == 1 then the top index is 10
            const Face c_side = Face(edge.second / 9);  // the face where the colored edge lies; 0 ... 5
            const Face green_side = Face(edge.first / 9);

            if (hasAlignedEdge(c_edge))
            {
                aligned_faces.insert(c_edge);

                continue;
            }

            if (1 <= c_edge && c_edge <= 4 && 9 * c_edge + 3 <= edge.second && (9 * (c_edge + 1)) - 1 >= edge.second)
            {
                do
                    cube.rotateSide(c_edge);
                while (cube.getCube()[t_index] != c_edge && cube.getCube()[Constants::EDGE_MAP.at(t_index)] != 0);

                break;
            }

            if (c_side == 0)
            {

                const int N = Helpers::get_turns(c_edge, green_side);

                switch (N)
                {
                case 0:
                    // (2)

                    cube.rotateSide(Face::UP);
                    cube.rotateSide(Helpers::wrap_decrement(c_edge));
                    cube.rotateSide(Face::UP, -1);
                    cube.rotateSide(c_edge);

                    break;

                case 1:
                case -1:
                    cube.rotateSide(green_side, N * -1);
                    cube.rotateSide(c_edge, -1 * N);

                    break;

                case 2:
                    cube.rotateSide(Face::UP, -1);
                    cube.rotateSide(Helpers::wrap_decrement(c_edge));
                    cube.rotateSide(Face::UP);
                    cube.rotateSide(c_edge);

                    break;
                }

                break;
            }
            else if (c_side == 5)
            {
                const int N = Helpers::get_turns(c_edge, green_side);

                cube.rotateSide(Face::DOWN, -1 * N);
                cube.rotateSide(c_edge, -1);
                cube.rotateSide(Face::UP, -1);
                cube.rotateSide(Helpers::wrap_increment(c_edge));
                cube.rotateSide(Face::UP);

                break;
            }

            const int N = Helpers::get_turns(c_edge, c_side);

            if (N == -1 || N == 1)
            {
                if (Helpers::get_row(edge.second) == 0)
                {
                    cube.rotateSide(c_side, N * -1);
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
                        alignEdge(c_edge, N);
                    
                }
                else
                {
                    cube.rotateSide(Face::DOWN, N * -1);
                    cube.rotateSide(c_edge, 2);
                }
            }
            else if (N == 2)
            {
                if (Helpers::get_row(edge.second) == 0)
                {
                    if (aligned_faces.size() == 0)
                    {
                        cube.rotateSide(Face::UP, 2);

                        break;
                    }

                    cube.rotateSide(c_side, 2);
                }
                else if (Helpers::get_row(edge.second) == 1)
                    cube.rotateSide(c_side, Helpers::get_column(edge.second) == 0 ? -1 : 1);

                cube.rotateSide(Face::DOWN, 2);
                cube.rotateSide(c_edge, 2);

                break;
            }
        }

        sleep(1);

    }
}