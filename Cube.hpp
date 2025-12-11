#pragma once
#include "Face.hpp"
#include "Constants.hpp"
#include <array>
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

    const char faceToChar(const Face f) const;

public:
    Cube() { this->cube = Constants::INITIAL_CUBE; };
    Cube(const std::array<Face, 54> cube) { this->cube = cube; }

    void print() const;

    const std::vector<std::tuple<Face, int>> getMoves() const { return this->moves; };

    void rotateSide(const Face side, int turns = 1);
    void rotateSide(const uint8_t side, int turns = 1) { rotateSide(Face(side), turns); }

    const std::array<Face, 54> getCube() const { return this->cube; };
};
