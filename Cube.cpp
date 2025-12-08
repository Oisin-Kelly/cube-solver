#include "Cube.hpp"
#include "Constants.hpp"
#include <iostream>
#include <string>

Cube::Cube()
{
    cube = Constants::INITIAL_CUBE;

    rotateU(true);
}

void Cube::rotateFace(const Face face = Face::UP, const bool clockwise = true)
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

void Cube::rotateU(const bool clockwise = true)
{
    using namespace std;

    rotateFace(Face::UP, clockwise);

    const array<Face, 3> front = {cube[9], cube[10], cube[11]};
    const array<Face, 3> right = {cube[18], cube[19], cube[20]};
    const array<Face, 3> back = {cube[27], cube[28], cube[29]};
    const array<Face, 3> left = {cube[36], cube[37], cube[38]};

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

void Cube::rotateF(const bool clockwise = true)
{
    using namespace std;

    rotateFace(Face::FRONT, clockwise);

    const array<Face, 3> top = {cube[6], cube[7], cube[8]};
    const array<Face, 3> right = {cube[18], cube[21], cube[24]};
    const array<Face, 3> left = {cube[44], cube[41], cube[38]};
    const array<Face, 3> bottom = {cube[47], cube[46], cube[45]};

    if (clockwise)
    {
        cube[6] = left[0], cube[7] = left[1], cube[8] = left[2];
        cube[18] = top[0], cube[21] = top[1], cube[24] = top[2];
        cube[44] = bottom[0], cube[41] = bottom[1], cube[38] = bottom[2];
        cube[47] = right[0], cube[46] = right[1], cube[45] = right[2];
    }
    else
    {
        cube[6] = right[0], cube[7] = right[1], cube[8] = right[2];
        cube[18] = bottom[0], cube[21] = bottom[1], cube[24] = bottom[2];
        cube[44] = top[0], cube[41] = top[1], cube[38] = top[2];
        cube[47] = left[0], cube[46] = left[1], cube[45] = left[2];
    }
}

void Cube::rotateR(const bool clockwise = true)
{
    using namespace std;

    rotateFace(Face::RIGHT, clockwise);

    const array<Face, 3> top = {cube[8], cube[5], cube[2]};
    const array<Face, 3> back = {cube[27], cube[30], cube[33]};
    const array<Face, 3> bottom = {cube[53], cube[50], cube[47]};
    const array<Face, 3> front = {cube[17], cube[14], cube[11]};

    if (clockwise)
    {
        cube[8] = front[0], cube[5] = front[1], cube[2] = front[2];
        cube[27] = top[0], cube[30] = top[1], cube[33] = top[2];
        cube[53] = back[0], cube[50] = back[1], cube[47] = back[2];
        cube[17] = bottom[0], cube[14] = bottom[1], cube[11] = bottom[2];
    }
    else
    {
        cube[8] = back[0], cube[5] = back[1], cube[2] = back[2];
        cube[27] = bottom[0], cube[30] = bottom[1], cube[33] = bottom[2];
        cube[53] = front[0], cube[50] = front[1], cube[47] = front[2];
        cube[17] = top[0], cube[14] = top[1], cube[11] = top[2];
    }
}

void Cube::rotateB(const bool clockwise = true)
{
    using namespace std;

    rotateFace(Face::BACK, clockwise);

    const array<Face, 3> top = {cube[2], cube[1], cube[0]};
    const array<Face, 3> left = {cube[36], cube[39], cube[42]};
    const array<Face, 3> bottom = {cube[51], cube[52], cube[53]};
    const array<Face, 3> right = {cube[26], cube[23], cube[20]};

    if (clockwise)
    {
        cube[2] = right[0], cube[1] = right[1], cube[0] = right[2];
        cube[26] = bottom[0], cube[23] = bottom[1], cube[20] = bottom[2];
        cube[36] = top[0], cube[39] = top[1], cube[42] = top[2];
        cube[51] = left[0], cube[52] = left[1], cube[53] = left[2];
    }
    else
    {
        cube[2] = left[0], cube[1] = left[1], cube[0] = left[2];
        cube[26] = top[0], cube[23] = top[1], cube[20] = top[2];
        cube[36] = bottom[0], cube[39] = bottom[1], cube[42] = bottom[2];
        cube[51] = right[0], cube[52] = right[1], cube[53] = right[2];
    }
}

void Cube::rotateL(const bool clockwise = true)
{
    using namespace std;

    rotateFace(Face::LEFT, clockwise);

    const array<Face, 3> top = {cube[0], cube[3], cube[6]};
    const array<Face, 3> front = {cube[9], cube[12], cube[15]};
    const array<Face, 3> bottom = {cube[45], cube[48], cube[51]};
    const array<Face, 3> back = {cube[35], cube[32], cube[29]};

    if (clockwise)
    {
        cube[0] = back[0], cube[3] = back[1], cube[6] = back[2];
        cube[9] = top[0], cube[12] = top[1], cube[15] = top[2];
        cube[35] = bottom[0], cube[32] = bottom[1], cube[29] = bottom[2];
        cube[45] = front[0], cube[48] = front[1], cube[51] = front[2];
    }
    else
    {
        cube[0] = front[0], cube[3] = front[1], cube[6] = front[2];
        cube[9] = bottom[0], cube[12] = bottom[1], cube[15] = bottom[2];
        cube[35] = top[0], cube[32] = top[1], cube[29] = top[2];
        cube[45] = back[0], cube[48] = back[1], cube[51] = back[2];
    }
}

void Cube::rotateD(const bool clockwise = true)
{
    using namespace std;

    rotateFace(Face::DOWN, clockwise);

    const array<Face, 3> front = {cube[15], cube[16], cube[17]};
    const array<Face, 3> right = {cube[24], cube[25], cube[26]};
    const array<Face, 3> left = {cube[42], cube[43], cube[44]};
    const array<Face, 3> back = {cube[33], cube[34], cube[35]};

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

void Cube::print() const
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
    }
    cout << endl;

    cout << "BOTTOM:" << endl;
    for (int i = 45; i < 54; i++)
    {
        std::cout << static_cast<int>(cube[i]) << " ";
        if (takeNewLine(i - 45))
            cout << endl;
    }
    cout << endl;
}

std::vector<std::string> Cube::getMoves() const
{
    return moves;
}

void Cube::rotateSide(const Face side, int turns)
{
    if (turns == 0)
        return;

    const bool clockwise = turns > 0;
    const char *faceNames[] = {"U", "F", "R", "B", "L", "D"};

    std::string move = faceNames[side];
    int absTurns = abs(turns);
    if (absTurns == 2)
        move += "2";
    else if (!clockwise)
        move += "'";
    moves.push_back(move);

    turns = absTurns;

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

const std::array<Face, 54> Cube::getCube() const
{
    return cube;
}

const Face Cube::operator[](const uint8_t index) const
{
    return cube[index];
}