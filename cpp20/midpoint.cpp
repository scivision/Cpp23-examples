// https://en.cppreference.com/w/cpp/numeric/midpoint

#include <cstdint>
#include <iostream>
#include <limits>
#include <numeric>
#include <cstdlib>

#ifndef __cpp_lib_interpolate
#error "std::midpoint is not available"
#endif


int main()
{
    std::uint32_t a = std::numeric_limits<std::uint32_t>::max();
    std::uint32_t b = std::numeric_limits<std::uint32_t>::max() - 2;

    std::cout << "a: " << a << '\n'
              << "b: " << b << '\n'
              << "Incorrect (overflow and wrapping): " << (a + b) / 2 << '\n'
              << "Correct: " << std::midpoint(a, b) << "\n\n";

    auto on_pointers = [](int i, int j)
    {
        char const* text = "0123456789";
        char const* p = text + i;
        char const* q = text + j;
        std::cout << "std::midpoint('" << *p << "', '" << *q << "'): '"
                  << *std::midpoint(p, q) << "'\n";
    };

    on_pointers(2, 4);
    on_pointers(2, 5);
    on_pointers(5, 2);
    on_pointers(2, 6);

    return EXIT_SUCCESS;
}
