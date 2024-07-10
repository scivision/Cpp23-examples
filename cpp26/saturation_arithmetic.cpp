// https://en.cppreference.com/w/cpp/numeric/saturate_cast

#include <cstdint>
#include <limits>
#include <numeric>
#include <cstdlib>
#include <iostream>

int main()
{
    constexpr std::int16_t x1{696};

    constexpr std::int8_t x2 = std::saturate_cast<std::int8_t>(x1);
    static_assert(x2 == std::numeric_limits<std::int8_t>::max());

    constexpr std::uint8_t x3 = std::saturate_cast<std::uint8_t>(x1);
    static_assert(x3 == std::numeric_limits<std::uint8_t>::max());

    constexpr std::int16_t y1{-696};

    constexpr std::int8_t y2 = std::saturate_cast<std::int8_t>(y1);
    static_assert(y2 == std::numeric_limits<std::int8_t>::min());

    constexpr std::uint8_t y3 = std::saturate_cast<std::uint8_t>(y1);
    static_assert(y3 == 0);

    std::cout << "OK: saturate_cast\n";

    return EXIT_SUCCESS;
}
