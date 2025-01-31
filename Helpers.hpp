#pragma once
#include "Face.hpp"

namespace Helpers {
    const Face wrapDecrement(const Face face);
    const Face wrapIncrement(const Face face);
    const uint8_t wrap_subtract(const uint8_t minuend, const uint8_t subtrahend);
    const int getTurns(const Face from, const Face to);
    const uint8_t get_column(uint8_t index);
    const uint8_t get_row(uint8_t index);
}
