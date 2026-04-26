#include <gtest/gtest.h>
#include "CubeSolverLib.hpp"

using Move = std::tuple<Face, int>;

static Move m(Face f, int t) { return {f, t}; }

TEST(OptimiseMoves, NoOp)
{
    // Arrange
    std::vector<Move> moves = {m(Face::UP, 1), m(Face::FRONT, 1)};

    // Act
    auto result = optimiseMoves(moves);

    // Assert
    EXPECT_EQ(result, moves);
}

TEST(OptimiseMoves, MergeConsecutiveSameFace)
{
    // Arrange
    std::vector<Move> input = {m(Face::UP, 1), m(Face::UP, 1), m(Face::UP, 1)};

    // Act
    auto result = optimiseMoves(input);

    // Assert — U U U -> U3 (3 % 4 = 3, equivalent to U', caught in notation)
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(std::get<0>(result[0]), Face::UP);
    EXPECT_EQ(std::get<1>(result[0]), 3);
}

TEST(OptimiseMoves, CancelInverse)
{
    // Arrange
    std::vector<Move> input = {m(Face::UP, 1), m(Face::UP, -1)};

    // Act
    auto result = optimiseMoves(input);

    // Assert — U U' -> empty
    EXPECT_TRUE(result.empty());
}

TEST(OptimiseMoves, CancelRepeatedInverse)
{
    // Arrange
    std::vector<Move> input = {m(Face::UP, 1), m(Face::UP, -1), m(Face::UP, 1), m(Face::UP, -1)};

    // Act
    auto result = optimiseMoves(input);

    // Assert — U U' U U' -> empty
    EXPECT_TRUE(result.empty());
}

TEST(OptimiseMoves, CancelNestedInverse)
{
    // Arrange
    std::vector<Move> input = {m(Face::DOWN, 1), m(Face::UP, 1), m(Face::UP, -1), m(Face::UP, 1), m(Face::UP, -1), m(Face::DOWN, -1)};

    // Act
    auto result = optimiseMoves(input);

    // Assert — D U U' U U' D' -> empty
    EXPECT_TRUE(result.empty());
}

TEST(OptimiseMoves, NonAdjacentSameFaceUnchanged)
{
    // Arrange
    std::vector<Move> input = {m(Face::UP, 1), m(Face::FRONT, 1), m(Face::UP, 1)};

    // Act
    auto result = optimiseMoves(input);

    // Assert — U F U can't merge, F is in between
    EXPECT_EQ(result, input);
}

TEST(OptimiseMoves, HalfTurn)
{
    // Arrange
    std::vector<Move> input = {m(Face::UP, 2), m(Face::UP, 2)};

    // Act
    auto result = optimiseMoves(input);

    // Assert — U2 U2 -> cancel
    EXPECT_TRUE(result.empty());
}
