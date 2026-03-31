// https://en.cppreference.com/w/cpp/algorithm/ranges/iota.html

#include <algorithm> // for std::ranges::shuffle
#include <functional> // for std::identity
#include <iostream>
#include <list>
#include <numeric> // for std::ranges::iota
#include <random>  // for std::mt19937 and std::random_device
#include <vector>

#ifndef __cpp_lib_ranges_iota
#error "std::ranges::iota is not supported"
#endif

template <typename Proj = std::identity>
void println(auto comment, std::ranges::input_range auto&& range, Proj proj = {})
{
    for (std::cout << comment; auto const &element : range)
        std::cout << proj(element) << ' ';
    std::cout << '\n';
}

int main()
{
    std::list<int> list(8);

    // Fill the list with ascending values: 0, 1, 2, ..., 7
    std::ranges::iota(list, 0);
    println("List: ", list);

    // A vector of iterators (see the comment to Example)
    std::vector<std::list<int>::iterator> vec(list.size());

    // Fill with iterators to consecutive list's elements
    std::ranges::iota(vec.begin(), vec.end(), list.begin());

    std::ranges::shuffle(vec, std::mt19937 {std::random_device {}()});
    println("List viewed via vector: ", vec, [](auto it) { return *it; });

    return 0;
}
