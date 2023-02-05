// https://godbolt.org/z/xna774
// https://stackoverflow.com/a/444614

#include <algorithm>
#include <array>
#include <cstring>
#include <functional>
#include <limits>
#include <random>
#include <string>

#include <iostream>
#include <cstdlib>


template <typename T = std::mt19937>
auto random_generator() -> T {
    auto constexpr seed_bits = sizeof(typename T::result_type) * T::state_size;
    auto constexpr seed_len = seed_bits / std::numeric_limits<std::seed_seq::result_type>::digits;
    auto seed = std::array<std::seed_seq::result_type, seed_len>{};
    auto dev = std::random_device{};
    std::generate_n(begin(seed), seed_len, std::ref(dev));
    auto seed_seq = std::seed_seq(begin(seed), end(seed));
    return T{seed_seq};
}

auto generate_random_alphanumeric_string(std::size_t len) -> std::string {
    static constexpr auto chars =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    thread_local auto rng = random_generator<>();
    auto dist = std::uniform_int_distribution{{}, std::strlen(chars) - 1};
    auto result = std::string(len, '\0');
    std::generate_n(begin(result), len, [&]() { return chars[dist(rng)]; });
    return result;
}

int main() {
    auto s = generate_random_alphanumeric_string(10);
    std::cout << s << std::endl;
    return EXIT_SUCCESS;
}
