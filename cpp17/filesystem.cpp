#include <iostream>
#include <cstdlib>
#include <filesystem>


namespace fs = std::filesystem;

int main() {

  std::cout << "temporary dir: " << fs::temp_directory_path() << std::endl;
  std::cout << "current dir: " << fs::current_path() << std::endl;

  return EXIT_SUCCESS;
}
