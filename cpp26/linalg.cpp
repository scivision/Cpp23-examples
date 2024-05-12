// https://en.cppreference.com/w/cpp/numeric/linalg
#include <cassert>
#include <cstddef>
#include <linalg>
#include <mdspan>
#include <numeric>
#include <vector>
#include <cstdlib>

#if __has_include(<execution>)
#include <execution>
#endif

int main()
{
    constexpr std::size_t N = 40;
    std::vector<double> x_vec(N);
    std::ranges::iota(x_vec, 0);

    std::mdspan x(x_vec.data(), N);

    // x[i] *= 2.0, executed sequentially
    std::linalg::scale(2.0, x);

#if __has_include(<execution>)
    // x[i] *= 3.0, executed in parallel
    std::linalg::scale(std::execution::par_unseq, 3.0, x);
#endif

    for (std::size_t i{}; i != N; ++i)
        assert(x[i] == 6.0 * static_cast<double>(i));

    return EXIT_SUCCESS;
}
