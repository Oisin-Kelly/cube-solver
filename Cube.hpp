#pragma once
#include <array>
#include "Face.hpp"

class Cube {
    private:
        std::array<Face, 54>  cube;

        void rotateFace(const Face side, const bool clockwise);
        void rotateU(const bool clockwise);
        void rotateF(const bool clockwise);
        void rotateR(const bool clockwise);
        void rotateB(const bool clockwise);
        void rotateL(const bool clockwise);
        void rotateD(const bool clockwise);


    public:
        Cube();

        void print();


        void rotateSide(const Face side, int turns = 1);
        const std::array<Face, 54> getCube() const;
};
