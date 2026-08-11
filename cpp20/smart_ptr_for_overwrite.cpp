#include <memory>
#include <string>
#include <cstring>
#include <iostream>
#include <cstdlib>

std::string append_hello(std::string s){
  // many functions require char; this is a toy example
  // showing use of std::make_unique<char[]> as a safe buffer

  auto c1 = std::make_unique_for_overwrite<char[]>(s.size() + 6);

  std::memcpy(c1.get(), s.c_str(), s.size());
  std::memcpy(c1.get() + s.size(), "hello", 6);

  return std::string(c1.get());
}

int main(){

    std::cout << append_hello("Good morning ") << "\n";

    return EXIT_SUCCESS;
}
