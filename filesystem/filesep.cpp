#include <iostream>
#include <filesystem>

int main(){

std::cout << "filesep: " << std::filesystem::path::preferred_separator << std::endl;

return EXIT_SUCCESS;
}
