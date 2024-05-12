// https://en.cppreference.com/w/cpp/iterator/projected
#include <algorithm>

#include <functional>
#include <iterator>

#include <cstdlib>
#include <iostream>

template<class T>
struct Holder
{
    T t;
};

struct Incomplete;

using P = Holder<Incomplete>*;

static_assert(std::equality_comparable<P>); // OK
static_assert(std::indirectly_comparable<P*, P*, std::equal_to<>>); // Error before C++26
static_assert(std::sortable<P*>); // Error before C++26

int main()
{

P a[10] = {}; // ten null pointers

if(auto c = std::count(a, a + 10, nullptr); c != 10){
  std::cerr << "Expected 10 nullptrs but got " << c << "\n";
  return EXIT_FAILURE;
}

if(auto c = std::ranges::count(a, a + 10, nullptr); c != 10){
  // Error before C++26
  std::cerr << "Expected 10 nullptrs but got " << c << "\n";
  return EXIT_FAILURE;
}

std::cout << "OK: ADL projected\n";
return EXIT_SUCCESS;
}
