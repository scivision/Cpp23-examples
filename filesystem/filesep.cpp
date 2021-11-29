#include <cassert>
#include <filesystem>

int main(){

char sep = std::filesystem::path::preferred_separator;
#ifdef _WIN32
  assert (sep == '\\');
#else
  assert (sep == '/');
#endif

return EXIT_SUCCESS;
}
