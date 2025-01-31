#include <array>
#include <string_view>
#include <iostream>
#include <map>
#include <unistd.h>
#include <unordered_set>

typedef std::array<std::uint8_t, 54> Cube;

int moves = 0;

bool take_newline(int i)
{
    return (i + 1) % 3 == 0;
}

constexpr int wrap_decrement(const int i)
{
    return i == 1 ? 4 : i - 1;
}

constexpr int wrap_increment(const int i)
{
    return i == 4 ? 1 : i + 1;
}

constexpr int wrap_subtract(const int minuend, const int subtrahend)
{
    constexpr uint8_t lower = 12;
    constexpr uint8_t upper = 41;
    constexpr uint8_t range = upper - lower + 1;

    return ((minuend - subtrahend - lower) % range + range) % range + lower;
}

constexpr int get_turns(int from, int to)
{
    int clockwise = (to - from + 4) % 4;
    int anti_clockwise = (from - to + 4) % 4;

    return clockwise <= anti_clockwise ? clockwise : -anti_clockwise;
}

constexpr int get_column(int index)
{
    return index % 3;
}

constexpr int get_row(int index)
{
    return (index / 3 + 3) % 3;
}

enum Face
{
    TOP = 0,
    FRONT,
    RIGHT,
    BACK,
    LEFT,
    BOTTOM
};



constexpr Cube INITIAL_CUBE = {
    0, 0, 0, // 0 - 2
    0, 0, 0, // top down view, FRONT facing me and BACK facing away // 3 - 5
    0, 0, 0, // 6 - 8

    1, 1, 1, // 9 - 11
    1, 1, 1, // with TOP on top // 12 - 14
    1, 1, 1, // 15 - 17
    2, 2, 2, // 18 - 20
    2, 2, 2, // 21 - 23
    2, 2, 2, // 24 - 26
    3, 3, 3, // 27 - 29
    3, 3, 3, // 30 - 32
    3, 3, 3, // 33 - 35
    4, 4, 4, // 36 - 38
    4, 4, 4, // 39 - 41
    4, 4, 4, // 42 - 44

    5, 5, 5,  // 45 - 47
    5, 5, 5,  // top down view, FRONT facing away and BACK facing me // 48 - 50
    5, 5, 5}; // 51 - 53

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

const std::map<int, std::tuple<int, int, int>> CORNER_MAP = {
    {6, {6, 38, 9}},
    {38, {6, 38, 9}},
    {9, {6, 38, 9}},
    {11, {8, 11, 18}}
};

void rotateFace(Cube &cube, int face = 0, bool anti_clockwise = false)
{
    using namespace std;

    array<uint8_t, 9> transforms = {6, 3, 0, 7, 4, 1, 8, 5, 2};

    if (anti_clockwise)
        transforms = {2, 5, 8, 1, 4, 7, 0, 3, 6};

    array<uint8_t, 9> temp;

    for (int i = 0; i < 9; ++i)
        temp[i] = cube[i + face * 9];

    for (int i = 0; i < 9; ++i)
        cube[face * 9 + i] = temp[transforms[i]];
}

const std::unordered_set<uint8_t> get_aligned_faces(const Cube cube)
{
    std::unordered_set<uint8_t> aligned_faces;

    if (cube[7] == 0 && cube[10] == 1)
        aligned_faces.insert(1);
    else if (cube[5] == 0 && cube[19] == 2)
        aligned_faces.insert(2);
    else if (cube[5] == 0 && cube[19] == 2)
        aligned_faces.insert(3);
    else if (cube[5] == 0 && cube[19] == 2)
        aligned_faces.insert(4);

    return aligned_faces;
}

void rotateU(Cube &cube, bool anti_clockwise = false)
{
    using namespace std;

    rotateFace(cube, 0, anti_clockwise);

    array<uint8_t, 3> front = {cube[9], cube[10], cube[11]};
    array<uint8_t, 3> right = {cube[18], cube[19], cube[20]};
    array<uint8_t, 3> back = {cube[27], cube[28], cube[29]};
    array<uint8_t, 3> left = {cube[36], cube[37], cube[38]};

    if (anti_clockwise)
    {
        cube[9] = left[0], cube[10] = left[1], cube[11] = left[2];
        cube[18] = front[0], cube[19] = front[1], cube[20] = front[2];
        cube[27] = right[0], cube[28] = right[1], cube[29] = right[2];
        cube[36] = back[0], cube[37] = back[1], cube[38] = back[2];
    }
    else
    {
        cube[9] = right[0], cube[10] = right[1], cube[11] = right[2];
        cube[18] = back[0], cube[19] = back[1], cube[20] = back[2];
        cube[27] = left[0], cube[28] = left[1], cube[29] = left[2];
        cube[36] = front[0], cube[37] = front[1], cube[38] = front[2];
    }
}

void rotateF(Cube &cube, bool anti_clockwise = false)
{
    using namespace std;

    rotateFace(cube, 1, anti_clockwise);

    array<uint8_t, 3> top = {cube[6], cube[7], cube[8]};
    array<uint8_t, 3> right = {cube[18], cube[21], cube[24]};
    array<uint8_t, 3> left = {cube[38], cube[41], cube[44]};
    array<uint8_t, 3> bottom = {cube[45], cube[46], cube[47]};

    if (anti_clockwise)
    {
        cube[6] = right[0], cube[7] = right[1], cube[8] = right[2];
        cube[18] = bottom[0], cube[21] = bottom[1], cube[24] = bottom[2];
        cube[38] = top[0], cube[41] = top[1], cube[44] = top[2];
        cube[45] = left[0], cube[46] = left[1], cube[47] = left[2];
    }
    else
    {
        cube[6] = left[0], cube[7] = left[1], cube[8] = left[2];
        cube[18] = top[0], cube[21] = top[1], cube[24] = top[2];
        cube[38] = bottom[0], cube[41] = bottom[1], cube[44] = bottom[2];
        cube[45] = right[0], cube[46] = right[1], cube[47] = right[2];
    }
}

void rotateR(Cube &cube, bool anti_clockwise = false)
{
    using namespace std;

    rotateFace(cube, 2, anti_clockwise);

    array<uint8_t, 3> top = {cube[2], cube[5], cube[8]};
    array<uint8_t, 3> back = {cube[27], cube[30], cube[33]};
    array<uint8_t, 3> bottom = {cube[47], cube[50], cube[53]};
    array<uint8_t, 3> front = {cube[11], cube[14], cube[17]};

    if (anti_clockwise)
    {
        cube[2] = back[0], cube[5] = back[1], cube[8] = back[2];
        cube[27] = bottom[0], cube[30] = bottom[1], cube[33] = bottom[2];
        cube[47] = front[0], cube[50] = front[1], cube[53] = front[2];
        cube[11] = top[0], cube[14] = top[1], cube[17] = top[2];
    }
    else
    {
        cube[2] = front[0], cube[5] = front[1], cube[8] = front[2];
        cube[27] = top[0], cube[30] = top[1], cube[33] = top[2];
        cube[47] = back[0], cube[50] = back[1], cube[53] = back[2];
        cube[11] = bottom[0], cube[14] = bottom[1], cube[17] = bottom[2];
    }
}

void rotateB(Cube &cube, bool anti_clockwise = false)
{
    using namespace std;

    rotateFace(cube, 3, anti_clockwise);

    array<uint8_t, 3> top = {cube[0], cube[1], cube[2]};
    array<uint8_t, 3> right = {cube[20], cube[23], cube[26]};
    array<uint8_t, 3> left = {cube[36], cube[39], cube[42]};
    array<uint8_t, 3> bottom = {cube[51], cube[52], cube[53]};

    if (anti_clockwise)
    {
        cube[0] = left[0], cube[1] = left[1], cube[2] = left[2];
        cube[20] = top[0], cube[23] = top[1], cube[26] = top[2];
        cube[36] = bottom[0], cube[39] = bottom[1], cube[42] = bottom[2];
        cube[51] = right[0], cube[52] = right[1], cube[53] = right[2];
    }
    else
    {
        cube[0] = right[0], cube[1] = right[1], cube[2] = right[2];
        cube[20] = bottom[0], cube[23] = bottom[1], cube[26] = bottom[2];
        cube[36] = top[0], cube[39] = top[1], cube[42] = top[2];
        cube[51] = left[0], cube[52] = left[1], cube[53] = left[2];
    }
}

void rotateL(Cube &cube, bool anti_clockwise = false)
{
    using namespace std;

    rotateFace(cube, 4, anti_clockwise);

    array<uint8_t, 3> top = {cube[0], cube[3], cube[6]};
    array<uint8_t, 3> front = {cube[9], cube[12], cube[15]};
    array<uint8_t, 3> back = {cube[29], cube[32], cube[35]};
    array<uint8_t, 3> bottom = {cube[45], cube[48], cube[51]};

    if (anti_clockwise)
    {
        cube[0] = front[0], cube[3] = front[1], cube[6] = front[2];
        cube[9] = bottom[0], cube[12] = bottom[1], cube[15] = bottom[2];
        cube[29] = top[0], cube[32] = top[1], cube[35] = top[2];
        cube[45] = back[0], cube[48] = back[1], cube[51] = back[2];
    }
    else
    {
        cube[0] = back[0], cube[3] = back[1], cube[6] = back[2];
        cube[9] = top[0], cube[12] = top[1], cube[15] = top[2];
        cube[29] = bottom[0], cube[32] = bottom[1], cube[35] = bottom[2];
        cube[45] = front[0], cube[48] = front[1], cube[51] = front[2];
    }
}

void rotateD(Cube &cube, bool anti_clockwise = false)
{
    using namespace std;

    rotateFace(cube, 5, anti_clockwise);

    array<uint8_t, 3> front = {cube[15], cube[16], cube[17]};
    array<uint8_t, 3> left = {cube[42], cube[43], cube[44]};
    array<uint8_t, 3> back = {cube[33], cube[34], cube[35]};
    array<uint8_t, 3> right = {cube[24], cube[25], cube[26]};

    if (anti_clockwise)
    {
        cube[15] = right[0], cube[16] = right[1], cube[17] = right[2];
        cube[42] = front[0], cube[43] = front[1], cube[44] = front[2];
        cube[33] = left[0], cube[34] = left[1], cube[35] = left[2];
        cube[24] = back[0], cube[25] = back[1], cube[26] = back[2];
    }
    else
    {
        cube[15] = left[0], cube[16] = left[1], cube[17] = left[2];
        cube[42] = back[0], cube[43] = back[1], cube[44] = back[2];
        cube[33] = right[0], cube[34] = right[1], cube[35] = right[2];
        cube[24] = front[0], cube[25] = front[1], cube[26] = front[2];
    }
}

void print_cube(Cube &cube)
{
    using namespace std;

    cout << "TOP:" << endl;
    for (int i = 0; i < 9; i++)
    {
        cout << static_cast<int>(cube[i]) << " ";
        if (take_newline(i))
            cout << endl;;
    }

    cout << "\nFRONT   RIGHT    BACK    LEFT" << endl;
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
        cout << endl;;
    }
    cout << endl;;

    cout << "BOTTOM:" << endl;;
    for (int i = 45; i < 54; i++)
    {
        std::cout << static_cast<int>(cube[i]) << " ";
        if (take_newline(i - 45))
            cout << endl;;
    }
    cout << endl;;
}


void rotate_side(Cube &cube, int face, int turns = 1)
{
    if (turns == 0)
        return;

    bool anti_clockwise = false;

    if (turns < 0)
        anti_clockwise = true;

    turns = abs(turns);

    for (int i = 0; i < turns; ++i)
    {
        std::cout << "rotating side " << face << " " << "anticlockwise: " << anti_clockwise << std::endl;
        switch (face)
        {
        case 0:
            rotateU(cube, anti_clockwise);
            break;
        case 1:
            rotateF(cube, anti_clockwise);
            break;
        case 2:
            rotateR(cube, anti_clockwise);
            break;
        case 3:
            rotateB(cube, anti_clockwise);
            break;
        case 4:
            rotateL(cube, anti_clockwise);
            break;
        case 5:
            rotateD(cube, anti_clockwise);
            break;
        }
        moves++;
        print_cube(cube);
    }
}

void align_edge(Cube &cube, uint8_t face, int N)
{
    if (N == 1)
    {
        rotate_side(cube, Face::TOP, -1);
        rotate_side(cube, wrap_increment(face));
        rotate_side(cube, Face::TOP);
    }
    else
    {
        rotate_side(cube, Face::TOP);
        rotate_side(cube, wrap_decrement(face), -1);
        rotate_side(cube, Face::TOP, -1);
    }
}

// Example usage
int main()
{
    Cube cube = INITIAL_CUBE;

    // Perform some moves

    print_cube(cube);

    rotateB(cube);
    rotateU(cube);
    rotateB(cube);
    rotateL(cube);
    rotateD(cube);
    rotateL(cube);
    rotateD(cube);
    rotateU(cube);
    rotateL(cube);
    rotateR(cube);
    rotateF(cube);
    rotateF(cube);
    rotateB(cube);
    rotateU(cube);
    rotateB(cube);
    rotateL(cube);
    rotateD(cube);
    rotateL(cube);
    rotateD(cube);
    rotateU(cube);
    rotateL(cube);
    rotateR(cube);
    rotateF(cube);
    rotateF(cube);

    print_cube(cube);

    std::unordered_set<uint8_t> aligned_faces = get_aligned_faces(cube);

    while (aligned_faces.size() != 4)
    {
        for (auto const edge : EDGE_MAP)
        {
            if (cube[edge.first] != 0)
                continue;

            std::cout << edge.first << std::endl;

            const uint8_t c_edge = cube[edge.second]; // edge number for colored side of edge; 1 .. 5
            const uint8_t t_index = c_edge * 9 + 1;   // top index of edge for eg. If c_edge == 1 then the top index is 10
            const uint8_t c_side = edge.second / 9;   // the face where the colored edge lies; 0 ... 5
            const uint8_t green_side = edge.first / 9;

            auto has_aligned_edge = [cube](uint8_t face)
            {
                const uint8_t t_index = face * 9 + 1;

                return cube[t_index] == face && cube[EDGE_MAP.at(t_index)] == 0;
            };

            if (has_aligned_edge(c_edge))
            {
                std::cout << "Has aligned edge: " << (int)c_edge << " " << edge.second << std::endl;

                aligned_faces.insert(c_edge);

                continue;
            }

            if (1 <= c_edge && c_edge <= 4 && 9 * c_edge + 3 <= edge.second && (9 * (c_edge + 1)) - 1 >= edge.second)
            {
                do
                    rotate_side(cube, c_edge);
                while (cube[t_index] != c_edge && cube[EDGE_MAP.at(t_index)] != 0);

                break;
            }

            if (c_side == 0)
            {

                const int N = get_turns(c_edge, green_side);

                switch (N)
                {
                case 0:
                    // (2)

                    rotate_side(cube, Face::TOP);
                    rotate_side(cube, wrap_decrement(c_edge));
                    rotate_side(cube, Face::TOP, -1);
                    rotate_side(cube, c_edge);

                    break;

                case 1:
                case -1:
                    rotate_side(cube, green_side, N * -1);
                    rotate_side(cube, c_edge, -N);

                    break;

                case 2:
                    rotate_side(cube, Face::TOP, -1);
                    rotate_side(cube, wrap_decrement(c_edge));
                    rotate_side(cube, Face::TOP);
                    rotate_side(cube, c_edge);

                    break;
                }

                break;
            }
            else if (c_side == 5)
            {
                const int N = get_turns(c_edge, green_side);

                rotate_side(cube, 5, -N);
                rotate_side(cube, c_edge, -1);
                rotate_side(cube, Face::TOP, -1);
                rotate_side(cube, wrap_increment(c_edge));
                rotate_side(cube, Face::TOP);

                break;
            }

            const int N = get_turns(c_edge, c_side);

            if (N == -1 || N == 1)
            {
                if (get_row(edge.second) == 0)
                {
                    rotate_side(cube, c_side, N * -1);
                    align_edge(cube, c_edge, N);
                }
                else if (get_row(edge.second) == 1)
                {
                    if (N == 1 && get_column(edge.second) == 2)
                    { 
                        rotate_side(cube, c_side, -2);
                        rotate_side(cube, Face::TOP, -1);
                        rotate_side(cube, c_side);
                        rotate_side(cube, Face::TOP);
                        rotate_side(cube, c_side);

                        break;
                    }
                    else if (N == -1 && get_column(edge.second) == 0)
                    {
                        rotate_side(cube, c_side, 2);
                        rotate_side(cube, Face::TOP);
                        rotate_side(cube, c_side, -1);
                        rotate_side(cube, Face::TOP, -1);
                        rotate_side(cube, c_side, -1);

                        break;
                    }
                    else
                    {
                        align_edge(cube, c_edge, N);
                    }
                }
                else
                {
                    rotate_side(cube, Face::BOTTOM, N * -1);
                    rotate_side(cube, c_edge, 2);
                }
            }
            else if (N == 2)
            {
                if (get_row(edge.second) == 0)
                {
                    if (aligned_faces.size() == 0)
                    {
                        rotate_side(cube, Face::TOP, 2);

                        break;
                    }

                    rotate_side(cube, c_side, 2);
                }
                else if (get_row(edge.second) == 1)
                    rotate_side(cube, c_side, get_column(edge.second) == 0 ? -1 : 1);
                
                rotate_side(cube, Face::BOTTOM, 2);
                rotate_side(cube, c_edge, 2);

                break;
            }
        }
        sleep(1);
    }

    std::cout << "Number of moves: " << moves << std::endl;

    return 0;
}
