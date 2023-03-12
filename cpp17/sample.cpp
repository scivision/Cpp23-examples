// https://stackoverflow.com/a/69753502

#include <algorithm>
#include <iterator>
#include <random>
#include <string>
#include <iostream>
#include <cstdlib>

static const char charset[] =
    "0123456789"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz";

template<typename URBG>
std::string gen_string(std::size_t length, URBG&& g) {
    std::string result;
    result.resize(length);
    std::sample(std::cbegin(charset),
                std::cend(charset),
                std::begin(result),
                std::intptr_t(length),
                std::forward<URBG>(g));

    return result;
}

int main() {
    std::mt19937 g;
    std::cout << gen_string(10, g) << std::endl;

    return EXIT_SUCCESS;
}
