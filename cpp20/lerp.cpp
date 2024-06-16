// https://en.cppreference.com/w/cpp/numeric/lerp

#include <cassert>
#include <cmath>
#include <iostream>
#include <cstdlib>

#ifndef __cpp_lib_interpolate
#error "std::lerp is not available"
#endif


float naive_lerp(float a, float b, float t)
{
    return a + t * (b - a);
}


int main()
{
    std::cout << std::boolalpha;

    const float a = 1e8f, b = 1.0f;
    const float midpoint = std::lerp(a, b, 0.5f);

    std::cout << "a = " << a << ", " << "b = " << b << '\n'
              << "midpoint = " << midpoint << '\n';

    std::cout << "std::lerp is exact: "
              << (a == std::lerp(a, b, 0.0f)) << ' '
              << (b == std::lerp(a, b, 1.0f)) << '\n';

    std::cout << "naive_lerp is exact: "
              << (a == naive_lerp(a, b, 0.0f)) << ' '
              << (b == naive_lerp(a, b, 1.0f)) << '\n';

    std::cout << "std::lerp(a, b, 1.0f) = " << std::lerp(a, b, 1.0f) << '\n'
              << "naive_lerp(a, b, 1.0f) = " << naive_lerp(a, b, 1.0f) << '\n';

    assert(not std::isnan(std::lerp(a, b, INFINITY))); // lerp here can be -inf

    std::cout << "Extrapolation demo, given std::lerp(5, 10, t):\n";
    for (auto t{-2.0}; t <= 2.0; t += 0.5)
        std::cout << std::lerp(5.0, 10.0, t) << ' ';
    std::cout << '\n';

    return EXIT_SUCCESS;
}
