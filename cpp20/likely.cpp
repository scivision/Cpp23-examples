// copied from https://en.cppreference.com/w/cpp/language/attributes/likely
#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <random>
#include <cstdlib>

namespace with_attributes {
constexpr double pow(double x, long long n) noexcept {
    if (n > 0) [[likely]]
        return x * pow(x, n - 1);
    else [[unlikely]]
        return 1;
}
constexpr long long fact(long long n) noexcept {
    if (n > 1) [[likely]]
        return n * fact(n - 1);
    else [[unlikely]]
        return 1;
}
constexpr double cos(double x) noexcept {
    constexpr long long precision{16LL};
    double y{};
    for (auto n{0LL}; n < precision; n += 2LL) [[likely]]
        y += pow(x, n) / (n & 2LL ? -fact(n) : fact(n));
    return y;
}
}  // namespace with_attributes

namespace no_attributes {
constexpr double pow(double x, long long n) noexcept {
    if (n > 0)
        return x * pow(x, n - 1);
    else
        return 1;
}
constexpr long long fact(long long n) noexcept {
    if (n > 1)
        return n * fact(n - 1);
    else
        return 1;
}
constexpr double cos(double x) noexcept {
    constexpr long long precision{16LL};
    double y{};
    for (auto n{0LL}; n < precision; n += 2LL)
        y += pow(x, n) / (n & 2LL ? -fact(n) : fact(n));
    return y;
}
}  // namespace no_attributes

double gen_random() noexcept {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<double> dis(-1.0, 1.0);
    return dis(gen);
}

volatile double sink{}; // ensures a side effect

int main() {
    for (const auto x : {0.125, 0.25, 0.5, 1. / (1 << 26)}) {
        std::cout
            << std::setprecision(53)
            << "x = " << x << '\n'
            << std::cos(x) << '\n'
            << with_attributes::cos(x) << '\n'
            << (std::cos(x) == with_attributes::cos(x) ? "equal" : "differ") << '\n';
    }

    auto benchmark = [](auto fun, auto rem) {
        const auto start = std::chrono::steady_clock::now();
        for (auto size{1ULL}; size != 1'000'000ULL; ++size) {
            sink = fun(gen_random());
        }
        const std::chrono::duration<double> diff =
            std::chrono::steady_clock::now() - start;
        std::cout << "Time: " << std::fixed << std::setprecision(6) << diff.count()
                  << " sec " << rem << std::endl;
    };

    benchmark(with_attributes::cos, "(with attributes)");
    benchmark(no_attributes::cos, "(without attributes)");
    benchmark([](double t) { return std::cos(t); }, "(std::cos)");

    return EXIT_SUCCESS;
}
