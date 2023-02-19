#include <cstdlib>

int main()
{
  int x = 0;

  switch (x) {
  case 0: [[fallthrough]];
  case 1: [[fallthrough]];
  case 2:
    return EXIT_SUCCESS;
  default:
    return EXIT_FAILURE;
  }
}
