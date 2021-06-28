// https://www.codingame.com/playgrounds/2205/7-features-of-c17-that-will-simplify-your-code/fold-expressions
#include <iostream>

template<typename ...Args> auto sum(Args ...args)
{
    return (args + ...);
}

int main()
{
    std::cout << sum(1, 2, 3, 4) << std::endl;

    return EXIT_SUCCESS;
}
