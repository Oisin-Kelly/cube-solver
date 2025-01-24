#include "Cube.hpp"
#include "Constants.hpp"
#include <iostream>

Cube::Cube()
{
    cube = Constants::INITIAL_CUBE;

    rotateB(true);
    rotateU(true);
    rotateB(true);
    rotateL(true);
    rotateD(true);
    rotateL(true);
    rotateD(true);
    rotateU(true);
    rotateL(true);
    rotateR(true);
    rotateF(true);
    rotateF(true);
    rotateB(true);
    rotateU(true);
    rotateB(true);
    rotateL(true);
    rotateD(true);
    rotateL(true);
    rotateD(true);
    rotateU(true);
    rotateL(true);
    rotateR(true);
    rotateF(true);
    rotateF(true);
}

void Cube::rotateFace(Face face = Face::UP, bool clockwise = true)
{
    using namespace std;

    array<uint8_t, 9> transforms = {6, 3, 0, 7, 4, 1, 8, 5, 2};

    if (!clockwise)
        transforms = {2, 5, 8, 1, 4, 7, 0, 3, 6};

    array<Face, 9> temp;

    for (int i = 0; i < 9; ++i)
        temp[i] = cube[i + face * 9];

    for (int i = 0; i < 9; ++i)
        cube[face * 9 + i] = temp[transforms[i]];
}

void Cube::rotateU(bool clockwise = true)
{
    using namespace std;

    rotateFace(Face::UP, clockwise);

    array<Face, 3> front = {cube[9], cube[10], cube[11]};
    array<Face, 3> right = {cube[18], cube[19], cube[20]};
    array<Face, 3> back = {cube[27], cube[28], cube[29]};
    array<Face, 3> left = {cube[36], cube[37], cube[38]};

    if (clockwise)
    {
        cube[9] = right[0], cube[10] = right[1], cube[11] = right[2];
        cube[18] = back[0], cube[19] = back[1], cube[20] = back[2];
        cube[27] = left[0], cube[28] = left[1], cube[29] = left[2];
        cube[36] = front[0], cube[37] = front[1], cube[38] = front[2];
    }
    else
    {
        cube[9] = left[0], cube[10] = left[1], cube[11] = left[2];
        cube[18] = front[0], cube[19] = front[1], cube[20] = front[2];
        cube[27] = right[0], cube[28] = right[1], cube[29] = right[2];
        cube[36] = back[0], cube[37] = back[1], cube[38] = back[2];
    }
}

void Cube::rotateF(bool clockwise = true)
{
    using namespace std;

    rotateFace(Face::FRONT, clockwise);

    array<Face, 3> top = {cube[6], cube[7], cube[8]};
    array<Face, 3> right = {cube[18], cube[21], cube[24]};
    array<Face, 3> left = {cube[38], cube[41], cube[44]};
    array<Face, 3> bottom = {cube[45], cube[46], cube[47]};

    if (clockwise)
    {
        cube[6] = left[0], cube[7] = left[1], cube[8] = left[2];
        cube[18] = top[0], cube[21] = top[1], cube[24] = top[2];
        cube[38] = bottom[0], cube[41] = bottom[1], cube[44] = bottom[2];
        cube[45] = right[0], cube[46] = right[1], cube[47] = right[2];
    }
    else
    {
        cube[6] = right[0], cube[7] = right[1], cube[8] = right[2];
        cube[18] = bottom[0], cube[21] = bottom[1], cube[24] = bottom[2];
        cube[38] = top[0], cube[41] = top[1], cube[44] = top[2];
        cube[45] = left[0], cube[46] = left[1], cube[47] = left[2];
    }
}

void Cube::rotateR(bool clockwise = true)
{
    using namespace std;

    rotateFace(Face::RIGHT, clockwise);

    array<Face, 3> top = {cube[2], cube[5], cube[8]};
    array<Face, 3> back = {cube[27], cube[30], cube[33]};
    array<Face, 3> bottom = {cube[47], cube[50], cube[53]};
    array<Face, 3> front = {cube[11], cube[14], cube[17]};

    if (clockwise)
    {
        cube[2] = front[0], cube[5] = front[1], cube[8] = front[2];
        cube[27] = top[0], cube[30] = top[1], cube[33] = top[2];
        cube[47] = back[0], cube[50] = back[1], cube[53] = back[2];
        cube[11] = bottom[0], cube[14] = bottom[1], cube[17] = bottom[2];
    }
    else
    {
        cube[2] = back[0], cube[5] = back[1], cube[8] = back[2];
        cube[27] = bottom[0], cube[30] = bottom[1], cube[33] = bottom[2];
        cube[47] = front[0], cube[50] = front[1], cube[53] = front[2];
        cube[11] = top[0], cube[14] = top[1], cube[17] = top[2];
    }
}

void Cube::rotateB(bool clockwise = true)
{
    using namespace std;

    rotateFace(Face::BACK, clockwise);

    array<Face, 3> top = {cube[0], cube[1], cube[2]};
    array<Face, 3> right = {cube[20], cube[23], cube[26]};
    array<Face, 3> left = {cube[36], cube[39], cube[42]};
    array<Face, 3> bottom = {cube[51], cube[52], cube[53]};

    if (clockwise)
    {
        cube[0] = right[0], cube[1] = right[1], cube[2] = right[2];
        cube[20] = bottom[0], cube[23] = bottom[1], cube[26] = bottom[2];
        cube[36] = top[0], cube[39] = top[1], cube[42] = top[2];
        cube[51] = left[0], cube[52] = left[1], cube[53] = left[2];
    }
    else
    {
        cube[0] = left[0], cube[1] = left[1], cube[2] = left[2];
        cube[20] = top[0], cube[23] = top[1], cube[26] = top[2];
        cube[36] = bottom[0], cube[39] = bottom[1], cube[42] = bottom[2];
        cube[51] = right[0], cube[52] = right[1], cube[53] = right[2];
    }
}

void Cube::rotateL(bool clockwise = true)
{
    using namespace std;

    rotateFace(Face::LEFT, clockwise);

    array<Face, 3> top = {cube[0], cube[3], cube[6]};
    array<Face, 3> front = {cube[9], cube[12], cube[15]};
    array<Face, 3> back = {cube[29], cube[32], cube[35]};
    array<Face, 3> bottom = {cube[45], cube[48], cube[51]};

    if (clockwise)
    {
        cube[0] = back[0], cube[3] = back[1], cube[6] = back[2];
        cube[9] = top[0], cube[12] = top[1], cube[15] = top[2];
        cube[29] = bottom[0], cube[32] = bottom[1], cube[35] = bottom[2];
        cube[45] = front[0], cube[48] = front[1], cube[51] = front[2];
    }
    else
    {
        cube[0] = front[0], cube[3] = front[1], cube[6] = front[2];
        cube[9] = bottom[0], cube[12] = bottom[1], cube[15] = bottom[2];
        cube[29] = top[0], cube[32] = top[1], cube[35] = top[2];
        cube[45] = back[0], cube[48] = back[1], cube[51] = back[2];
    }
}

void Cube::rotateD(bool clockwise = true)
{
    using namespace std;

    rotateFace(Face::DOWN, clockwise);

    array<Face, 3> front = {cube[15], cube[16], cube[17]};
    array<Face, 3> left = {cube[42], cube[43], cube[44]};
    array<Face, 3> back = {cube[33], cube[34], cube[35]};
    array<Face, 3> right = {cube[24], cube[25], cube[26]};

    if (clockwise)
    {
        cube[15] = left[0], cube[16] = left[1], cube[17] = left[2];
        cube[42] = back[0], cube[43] = back[1], cube[44] = back[2];
        cube[33] = right[0], cube[34] = right[1], cube[35] = right[2];
        cube[24] = front[0], cube[25] = front[1], cube[26] = front[2];
    }
    else
    {
        cube[15] = right[0], cube[16] = right[1], cube[17] = right[2];
        cube[42] = front[0], cube[43] = front[1], cube[44] = front[2];
        cube[33] = left[0], cube[34] = left[1], cube[35] = left[2];
        cube[24] = back[0], cube[25] = back[1], cube[26] = back[2];
    }
}

void Cube::print()
{
    using namespace std;

    const auto takeNewLine = [](const uint8_t i)
    {
        return (i + 1) % 3 == 0;
    };

    cout << "TOP:" << endl;
    for (int i = 0; i < 9; i++)
    {
        cout << static_cast<int>(cube[i]) << " ";
        if (takeNewLine(i))
            cout << endl;
        ;
    }

    cout << "\nFRONT   RIGHT   BACK    LEFT" << endl;
    for (int row = 0; row < 3; ++row)
    {
        for (int face = 1; face <= 4; ++face)
        {
            for (int col = 0; col < 3; ++col)
            {
                cout << static_cast<int>(cube[face * 9 + row * 3 + col]) << " ";
            }
            cout << "  ";
        }
        cout << endl;
        ;
    }
    cout << endl;
    ;

    cout << "BOTTOM:" << endl;
    ;
    for (int i = 45; i < 54; i++)
    {
        std::cout << static_cast<int>(cube[i]) << " ";
        if (takeNewLine(i - 45))
            cout << endl;
        ;
    }
    cout << endl;
    ;
}

void Cube::rotateSide(const Face side, int turns)
{
    std::cout << "rotating side " << (int)side << " by " << turns << std::endl;
    if (turns == 0)
        return;

    const bool clockwise = turns < 0 ? false : true;

    turns = abs(turns);

    for (int i = 0; i < turns; ++i)
    {
        switch (side)
        {
        case UP:
            rotateU(clockwise);
            break;
        case FRONT:
            rotateF(clockwise);
            break;
        case RIGHT:
            rotateR(clockwise);
            break;
        case BACK:
            rotateB(clockwise);
            break;
        case LEFT:
            rotateL(clockwise);
            break;
        case DOWN:
            rotateD(clockwise);
            break;
        }

        print();
    }
}

const std::array<Face, 54> Cube::getCube() const {
    return this->cube;
}