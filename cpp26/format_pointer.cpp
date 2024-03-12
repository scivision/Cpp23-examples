#include <cstdlib>

#include <cstdint>
#include <iostream>
#include <format>

int main(){
    int i = 0;
    std::cout << std::format("{:P}", i) << "\n";
    return EXIT_SUCCESS;
}
