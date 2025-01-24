#include "Helpers.hpp"

namespace Helpers {
    const Face wrap_decrement(const Face face) {
        return Face(face == 1 ? 4 : face - 1);
    }

    const Face wrap_increment(const Face face) {
        return Face(face == 4 ? 1 : face + 1);
    }

    const uint8_t wrap_subtract(const uint8_t minuend, const uint8_t subtrahend) {
        constexpr uint8_t lower = 12;
        constexpr uint8_t upper = 41;
        constexpr uint8_t range = upper - lower + 1;

        return ((minuend - subtrahend - lower) % range + range) % range + lower;
    }

    const int get_turns(const Face from, const Face to) {
        int clockwise = (to - from + 4) % 4;
        int anti_clockwise = (from - to + 4) % 4;

        return clockwise <= anti_clockwise ? clockwise : -anti_clockwise;
    }

    const uint8_t get_column(uint8_t index) {
        return index % 3;
    }

    const uint8_t get_row(uint8_t index) {
        return (index / 3 + 3) % 3;
    }
}