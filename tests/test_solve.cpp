#include <gtest/gtest.h>
#include "CubeSolverLib.hpp"
#include "Cube.hpp"
#include "Constants.hpp"

TEST(SolveCube, AlreadySolved)
{
    // Arrange
    auto state = Constants::INITIAL_CUBE;

    // Act
    auto result = solveCube(state);

    // Assert
    ASSERT_TRUE(result.success);
    EXPECT_TRUE(result.moves.empty());
}

TEST(SolveCube, SingleMove)
{
    // Arrange
    Cube c;
    c.rotateSide(Face::RIGHT, 1);

    // Act
    auto result = solveCube(c.getCube());

    // Assert
    ASSERT_TRUE(result.success);
    EXPECT_FALSE(result.moves.empty());
}

TEST(SolveCube, MultiMoveScramble)
{
    // Arrange
    Cube c;
    c.rotateSide(Face::UP, 1);
    c.rotateSide(Face::RIGHT, -1);
    c.rotateSide(Face::FRONT, 2);
    c.rotateSide(Face::DOWN, 1);
    c.rotateSide(Face::LEFT, -1);

    // Act
    auto result = solveCube(c.getCube());

    // Assert
    ASSERT_TRUE(result.success);
    EXPECT_FALSE(result.moves.empty());
}

TEST(SolveCube, IllegalCubeHitsMaxMoves)
{
    // Arrange — single corner twist (indices 8/11/18 form one corner).
    // Impossible to solve with legal moves, so the solver will exceed maxMoves
    auto bad = Constants::INITIAL_CUBE;
    bad[8] = Face::FRONT;
    bad[11] = Face::RIGHT;
    bad[18] = Face::UP;

    // Act
    auto result = solveCube(bad, 500);

    // Assert
    EXPECT_FALSE(result.success);
    EXPECT_FALSE(result.error.empty());
}
