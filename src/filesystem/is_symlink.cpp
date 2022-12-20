// Windows OK:
//   Visual Studio: cl /std:c++17 /EHsc is_sym.cpp
//   Clang: clang++ -std=c++17 is_sym.cpp
//   Intel oneAPI: icx/icl /std:c++17 is_sym.cpp
// Windows BROKEN:
//   says link is regular file: Windows GCC 11: g++ -std=c++17 is_sym.cpp
// Linux OK:
//   GCC >= 9: g++ -std=c++17 is_sym.cpp
//   GCC == 8: g++ -std=c++17 is_sym.cpp -lstdc++fs
// MacOS OK:
//   Clang: g++ -std=c++17 is_sym.cpp
//   Intel oneAPI: icpc -std=c++17 is_sym.cpp

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main(int argc, char **argv)
{

  if(argc != 3) {
    std::cerr << "please specify target link paths" << std::endl;
    return EXIT_FAILURE;
  }

  fs::path tgt = argv[1];
  fs::path lnk = argv[2];

  if(!fs::is_regular_file(tgt)) {
    std::cerr << "ERROR: target " << tgt << " is not a regular file" << std::endl;
    return EXIT_FAILURE;
  }

  if(!fs::exists(lnk)) {
    fs::create_symlink(tgt, lnk);
    std::cout << "created symlink: " << lnk << std::endl;
  }

  if(!fs::exists(lnk)) {
    std::cerr << lnk << " does not exist" << std::endl;
    return EXIT_FAILURE;
  }

  if(fs::is_symlink(lnk)) {
    std::cout << lnk << " is a symlink" << std::endl;
    return EXIT_SUCCESS;
  }

  std::cerr << "ERROR: symlink " << lnk << " is not a symlink, instead is a ";

  if(fs::is_regular_file(lnk)) {
    std::cerr << "regular file";
  }
  else if(fs::is_directory(lnk)) {
    std::cerr << "directory";
  }
  else {
    std::cerr << "special file";
  }

  std::cerr << std::endl;

  return EXIT_FAILURE;
}
