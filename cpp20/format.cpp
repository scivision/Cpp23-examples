#include <format>

#include <cstdlib>
#include <iostream>

int main(){
    std::cout << std::format("{}", __cpp_lib_format) << "\n";
    return EXIT_SUCCESS;
}
