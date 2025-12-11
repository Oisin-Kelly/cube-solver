#pragma once
#include <array>
#include "Face.hpp"
#include <string>
#include <vector>

class Cube
{
private:
    std::array<Face, 54> cube;
    std::vector<std::tuple<Face, int>> moves;

    void rotateFace(const Face side, const bool clockwise);
    void rotateU(const bool clockwise);
    void rotateF(const bool clockwise);
    void rotateR(const bool clockwise);
    void rotateB(const bool clockwise);
    void rotateL(const bool clockwise);
    void rotateD(const bool clockwise);

public:
    Cube();

    void print() const;
    std::vector<std::tuple<Face, int>> getMoves() const;

    void rotateSide(const Face side, int turns = 1);
    void rotateSide(const uint8_t side, int turns = 1) { rotateSide(Face(side), turns); }
    const std::array<Face, 54> getCube() const;

    const Face operator[](const uint8_t index) const;
};
