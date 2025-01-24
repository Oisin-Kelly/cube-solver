#pragma once
#include <array>
#include <map>
#include "Face.hpp"

namespace Constants
{
    constexpr Face G = Face::UP;
    constexpr Face R = Face::FRONT;
    constexpr Face W = Face::RIGHT;
    constexpr Face O = Face::BACK;
    constexpr Face Y = Face::LEFT;
    constexpr Face B = Face::DOWN;

    constexpr std::array<Face, 54> INITIAL_CUBE = {
        G, G, G, // 0 - 2
        G, G, G, // top down view, FRONT facing me and BACK facing away // 3 - 5
        G, G, G, // 6 - 8

        R, R, R, // 9 - 11
        R, R, R, // with TOP on top // 12 - 14
        R, R, R, // 15 - 17
        W, W, W, // 18 - 20
        W, W, W, // 21 - 23
        W, W, W, // 24 - 26
        O, O, O, // 27 - 29
        O, O, O, // 30 - 32
        O, O, O, // 33 - 35
        Y, Y, Y, // 36 - 38
        Y, Y, Y, // 39 - 41
        Y, Y, Y, // 42 - 44

        B, B, B,  // 45 - 47
        B, B, B,  // top down view, FRONT facing away and BACK facing me // 48 - 50
        B, B, B}; // 51 - 53

    const std::map<int, int> EDGE_MAP = {
        {1, 28}, // top high, back high
        {28, 1},
        {7, 10}, // top low, front high
        {10, 7},
        {3, 37}, // top left, left high
        {37, 3},
        {5, 19}, // top right, right high
        {19, 5},

        {16, 46}, // front low, bottom high
        {46, 16},
        {14, 21}, // front right, right left
        {21, 14},

        {25, 50}, // right low, bottom right
        {50, 25},
        {23, 30}, // right right, back left
        {30, 23},

        {34, 52}, // back low, bottom low
        {52, 34},
        {32, 39}, // back right, left left
        {39, 32},

        {43, 48}, // left low, bottom left
        {48, 43},
        {41, 12}, // left right, front left
        {12, 41}};

    const std::vector<std::tuple<int, int, int>> CORNERS = {
        {8, 11, 18},
        {2, 20, 27},
        {0, 29, 36},
        {6, 36, 9},
        {45, 15, 44},
        {51, 42, 35},
        {53, 33, 26},
        {47, 24, 17}};
}