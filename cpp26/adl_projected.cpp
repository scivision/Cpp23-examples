// https://en.cppreference.com/w/cpp/iterator/projected
#include <algorithm>
#include <cassert>
#include <functional>
#include <iterator>

#include <cstdlib>

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
    assert(std::count(a, a + 10, nullptr) == 10); // OK
    assert(std::ranges::count(a, a + 10, nullptr) == 10); // Error before C++26

    return EXIT_SUCCESS;
}
