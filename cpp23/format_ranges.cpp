// from https://en.cppreference.com/w/cpp/utility/format/format.html
#include <format>
#include <iostream>
#include <set>
#include <string_view>
#include <cstdlib>

int main()
{
const std::set<std::string_view> continents
{
    "Africa",   "America",      "Antarctica",
    "Asia",     "Australia",    "Europe"
};
std::cout << std::format("Hello {}!\n", continents);

return EXIT_SUCCESS;
}