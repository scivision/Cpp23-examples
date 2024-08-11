#include <iostream>
#include <cstdlib>
#include <filesystem>


namespace fs = std::filesystem;

int main() {

  std::cout << "temporary dir: " << fs::temp_directory_path() << "\n";
  std::cout << "current dir: " << fs::current_path() << "\n";

  return EXIT_SUCCESS;
}
