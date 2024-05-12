#include <cstdlib>

#include <cstdint>
#include <iostream>

#include <format>

#if __cpp_lib_format < 202304L
#error "std::format not available for pointers"
#endif

int main(){
    int i = 0;
    std::cout << std::format("{:P}", i) << "\n";
    return EXIT_SUCCESS;
}
