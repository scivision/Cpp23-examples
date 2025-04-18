// https://en.cppreference.com/w/cpp/ranges/enumerate_view

#include <initializer_list>
#include <iostream>
#include <map>
#include <ranges>
#include <vector>

#include <cstdlib>

int main()
{
    constexpr static auto v = {'A', 'B', 'C', 'D'};

    for (auto const [index, letter] : std::views::enumerate(v))
        std::cout << '(' << index << ':' << letter << ") ";
    std::cout << '\n';

#if __cpp_lib_ranges_to_container
    // create a map using the position of each element as key
    auto m = v | std::views::enumerate | std::ranges::to<std::map>();

    for (auto const [key, value] : m)
        std::cout << '[' << key << "]:" << value << ' ';
    std::cout << '\n';
#endif

    std::vector<int> numbers{1, 3, 5, 7};

    // num is mutable even with const, which does not propagate to reference to
    // make it const, use `std::views::enumerate(numbers) | std::views::as_const`
    // or `std::views::enumerate(std::as_const(numbers))`
    for (auto const [index, num] : std::views::enumerate(numbers))
    {
        ++num; // the type is int&
        std::cout << numbers[index] << ' ';
    }
    std::cout << '\n';

  return EXIT_SUCCESS;
}
