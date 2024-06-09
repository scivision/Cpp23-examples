// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2022/p2510r3.pdf

#include <cstdlib>

#include <cstdint>
#include <iostream>

#include <format>

// https://en.cppreference.com/w/cpp/utility/format
#if __cpp_lib_format < 202304L
#error "std::format not available for pointers"
#endif

int main(){
    int i = 0;
    std::cout << std::format("{:P}", i) << "\n";
    return EXIT_SUCCESS;
}
