// fill an array with consecutive numbers starting at 0, intead of explicit for loop
#include <iostream>
#include <numeric>
#include <cstdlib>

int main()
{
    int a[10];

    std::iota(std::begin(a), std::end(a), 0);

    for (auto i : a)
        std::cout << i << " ";
    std::cout << "\n";

    return EXIT_SUCCESS;
}
