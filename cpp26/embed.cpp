#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>

#ifndef __cpp_pp_embed
#error "Preprocessor support for embedding is not available"
#endif

int main()
{
    std::vector<int> v{
        #embed "data.txt"
    };
    assert(std::accumulate(v.begin(), v.end(), 0) == 6);

    std::cout << "OK: c++26 std::embed works as expected\n";

    return 0;
}
