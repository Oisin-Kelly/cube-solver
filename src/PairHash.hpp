#pragma once
#include <utility>
#include <cstddef>

struct PairHash
{
    template <typename T1, typename T2>
    std::size_t operator()(const std::pair<T1, T2> &pair) const
    {
        return pair.first ^ pair.second;
    }
};