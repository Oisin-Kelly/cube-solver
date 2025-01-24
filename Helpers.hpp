#pragma once
#include "Face.hpp"

namespace Helpers {
    const Face wrap_decrement(const Face face);
    const Face wrap_increment(const Face face);
    const uint8_t wrap_subtract(const uint8_t minuend, const uint8_t subtrahend);
    const int get_turns(const Face from, const Face to);
    const uint8_t get_column(uint8_t index);
    const uint8_t get_row(uint8_t index);
}
